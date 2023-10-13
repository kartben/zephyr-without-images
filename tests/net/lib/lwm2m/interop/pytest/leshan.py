# Copyright (c) 2023 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: Apache-2.0

from __future__ import annotations

import json
import binascii
import requests
from datetime import datetime

class Leshan:
    def __init__(self, url: str):
        self.api_url = url
        self.timeout = 10
        #self.format = 'TLV'
        self.format = "SENML_CBOR"
        try:
            resp = self.get('/security/clients')
            if not isinstance(resp, list):
                raise RuntimeError('Did not receive list of endpoints')
        except requests.exceptions.ConnectionError:
            raise RuntimeError('Leshan not responding')

    @staticmethod
    def handle_response(resp: requests.models.Response):
        """
        Handle the response received from the server.

        Parameters:
        - response: The response object received from the server.

        Returns:
        - dict: The parsed JSON response as a dictionary.

        Raises:
        - Exception: If the response indicates an error condition.
        """
        if resp.status_code >= 300 or resp.status_code < 200:
            raise RuntimeError(f'Error {resp.status_code}: {resp.text}')
        if len(resp.text):
            obj = json.loads(resp.text)
            return obj
        else:
            return None

    def get(self, path: str):
        """Send HTTP GET query"""
        params = {'timeout': self.timeout}
        if self.format is not None:
            params['format'] = self.format
        resp = requests.get(f'{self.api_url}{path}', params=params, timeout=self.timeout)
        return Leshan.handle_response(resp)

    def put_raw(self, path: str, data: str | dict | None = None, headers: dict | None = None):
        resp = requests.put(f'{self.api_url}{path}', data=data, headers=headers, timeout=self.timeout)
        return Leshan.handle_response(resp)

    def put(self, path: str, data: str | dict, uri_options: str = ''):
        if isinstance(data, dict):
            data = json.dumps(data)
        return self.put_raw(f'{path}?timeout={self.timeout}&format={self.format}' + uri_options, data=data, headers={'content-type': 'application/json'})

    def post(self, path: str, data: str | dict | None = None):
        if isinstance(data, dict):
            data = json.dumps(data)
        if data is not None:
            headers={'content-type': 'application/json'}
            uri_options = f'?timeout={self.timeout}&format={self.format}'
        else:
            headers=None
            uri_options = ''
        resp = requests.post(f'{self.api_url}{path}' + uri_options, data=data, headers=headers, timeout=self.timeout)
        return Leshan.handle_response(resp)

    def delete(self, path: str):
        resp = requests.delete(f'{self.api_url}{path}', timeout=self.timeout)
        return Leshan.handle_response(resp)

    def execute(self, endpoint: str, path: str):
        return self.post(f'/clients/{endpoint}/{path}')

    def write(self, endpoint: str, path: str, value: bool | int | str):
        if len(path.split('/')) == 3:
            kind = 'singleResource'
        else:
            kind = 'resourceInstance'
        rid = path.split('/')[-1]
        return self.put(f'/clients/{endpoint}/{path}', self._define_resource(rid, value, kind))

    def update_obj_instance(self, endpoint: str, path: str, resources: dict):
        data = self._define_obj_inst(path, resources)
        return self.put(f'/clients/{endpoint}/{path}', data, uri_options='&replace=false')

    def replace_obj_instance(self, endpoint: str, path: str, resources: dict):
        data = self._define_obj_inst(path, resources)
        return self.put(f'/clients/{endpoint}/{path}', data, uri_options='&replace=true')

    def create_obj_instance(self, endpoint: str, path: str, resources: dict):
        data = self._define_obj_inst(path, resources)
        path = '/'.join(path.split('/')[:-1]) # Create call should not have instance ID in path
        return self.post(f'/clients/{endpoint}/{path}', data)

    @classmethod
    def _type_to_string(cls, value):
        """
        Convert a Python value to its corresponding Leshan representation.

        Parameters:
        - value: The value to be converted.

        Returns:
        - str: The string representation of the value.
        """
        if isinstance(value, bool):
            return 'boolean'
        if isinstance(value, int):
            return 'integer'
        if isinstance(value, datetime):
            return 'time'
        return 'string'

    @classmethod
    def _convert_type(cls, value):
        if isinstance(value, datetime):
            return int(value.timestamp())
        else:
            return value

    def _define_obj_inst(self, path: str, resources: dict):
        data = {
            "kind": "instance",
            "id": int(path.split('/')[-1]),  # ID is last element of path
            "resources": []
        }
        for key, value in resources.items():
            if isinstance(value, dict):
                kind = 'multiResource'
            else:
                kind = 'singleResource'
            data['resources'].append(self._define_resource(key, value, kind))
        return data

    def _define_resource(self, rid, value, kind='singleResource'):
        if kind in ('singleResource', 'resourceInstance'):
            return {
                "id": rid,
                "kind": kind,
                "value": self._convert_type(value),
                "type": self._type_to_string(value)
            }
        if kind == 'multiResource':
            return {
                "id": rid,
                "kind": kind,
                "values": value,
                "type": self._type_to_string(list(value.values())[0])
            }
        raise RuntimeError(f'Unhandled type {kind}')

    def _decode_value(self, type, value):
        """
        Decode the Leshan representation of a value back to a Python value.
        """
        if type == 'BOOLEAN':
            return bool(value)
        if type == 'INTEGER':
            return int(value)
        return value

    def _decode_resource(self, content):
        """
        Decode the Leshan representation of a resource back to a Python dictionary.
        """
        if content['kind'] == 'singleResource' or content['kind'] == 'resourceInstance':
            return {content['id']: self._decode_value(content['type'], content['value'])}
        elif content['kind'] == 'multiResource':
            values = {}
            for riid, value in content['values'].items():
                values.update({int(riid): self._decode_value(content['type'], value)})
            return {content['id']: values}
        raise RuntimeError(f'Unhandled type {content["kind"]}')

    def _decode_obj_inst(self, content):
        """
        Decode the Leshan representation of an object instance back to a Python dictionary.
        """
        resources = {}
        for resource in content['resources']:
            resources.update(self._decode_resource(resource))
        return {content['id']: resources}

    def _decode_obj(self, content):
        """
        Decode the Leshan representation of an object back to a Python dictionary.
        """
        instances = {}
        for instance in content['instances']:
            instances.update(self._decode_obj_inst(instance))
        return {content['id']: instances}

    def read(self, endpoint: str, path: str):
        resp = self.get(f'/clients/{endpoint}/{path}')
        if not resp['success']:
            return resp
        content = resp['content']
        if content['kind'] == 'obj':
            return self._decode_obj(content)
        elif content['kind'] == 'instance':
            return self._decode_obj_inst(content)
        elif content['kind'] == 'singleResource' or content['kind'] == 'resourceInstance':
            return self._decode_value(content['type'], content['value'])
        elif content['kind'] == 'multiResource':
            return self._decode_resource(content)
        raise RuntimeError(f'Unhandled type {content["kind"]}')

    def composite_read(self, endpoint: str, paths: list[str]):
        paths = [path if path.startswith('/') else '/' + path for path in paths]
        parameters = {
            'pathformat': self.format,
            'nodeformat': self.format,
            'timeout': self.timeout,
            'paths': ','.join(paths)
        }
        resp = requests.get(f'{self.api_url}/clients/{endpoint}/composite', params=parameters, timeout=self.timeout)
        payload = Leshan.handle_response(resp)
        if not payload['status'] == 'CONTENT(205)':
            raise RuntimeError(f'No content received')
        data = {}
        for path, content in payload['content'].items():
            keys = [int(key) for key in path.lstrip("/").split('/')]
            if len(keys) == 1:
                data.update(self._decode_obj(content))
            elif len(keys) == 2:
                if keys[0] not in data:
                    data[keys[0]] = {}
                data[keys[0]].update(self._decode_obj_inst(content))
            elif len(keys) == 3:
                if keys[0] not in data:
                    data[keys[0]] = {}
                if keys[1] not in data[keys[0]]:
                    data[keys[0]][keys[1]] = {}
                data[keys[0]][keys[1]].update(self._decode_resource(content))
            elif len(keys) == 4:
                if keys[0] not in data:
                    data[keys[0]] = {}
                if keys[1] not in data[keys[0]]:
                    data[keys[0]][keys[1]] = {}
                if keys[2] not in data[keys[0]][keys[1]]:
                    data[keys[0]][keys[1]][keys[2]] = {}
                data[keys[0]][keys[1]][keys[2]].update(self._decode_resource(content))
            else:
                raise RuntimeError(f'Unhandled path {path}')
        print(f'Requested paths: {paths}')
        print(data)
        return data


    def composite_write(self, endpoint: str, resources: dict):
        """
        Do LwM2m composite write operation.

        Targeted resources are defined as a dictionary with the following structure:
        {
            "/1/0/1": 60,
            "/1/0/6": True,
            "/16/0/0": {
                "0": "aa",
                "1": "bb",
                "2": "cc",
                "3": "dd"
            }
        }

        Objects or object instances cannot be targeted.
        """
        data = { }
        parameters = {
            'pathformat': self.format,
            'nodeformat': self.format,
            'timeout': self.timeout
        }
        for path, value in resources.items():
            path = path if path.startswith('/') else '/' + path
            level = len(path.split('/')) - 1
            rid = int(path.split('/')[-1])
            if level == 3:
                if isinstance(value, dict):
                    value = self._define_resource(rid, value, kind='multiResource')
                else:
                    value = self._define_resource(rid, value)
            elif level == 4:
                value = self._define_resource(rid, value, kind='resourceInstance')
            else:
                raise RuntimeError(f'Unhandled path {path}')
            data[path] = value

        resp = requests.put(f'{self.api_url}/clients/{endpoint}/composite', params=parameters, json=data, timeout=self.timeout)
        return Leshan.handle_response(resp)

    def discover(self, endpoint: str, path: str):
        resp = self.handle_response(requests.get(f'{self.api_url}/clients/{endpoint}/{path}/discover', timeout=self.timeout))
        data = {}
        for obj in resp['objectLinks']:
            data[obj['url']] = obj['attributes']
        return data

    def create_psk_device(self, endpoint: str, passwd: str):
        psk = binascii.b2a_hex(passwd.encode()).decode()
        self.put('/security/clients/', f'{{"endpoint":"{endpoint}","tls":{{"mode":"psk","details":{{"identity":"{endpoint}","key":"{psk}"}} }} }}')

    def delete_device(self, endpoint: str):
        self.delete(f'/security/clients/{endpoint}')

    def create_bs_device(self, endpoint: str, server_uri: str, bs_passwd: str, passwd: str):
        psk = binascii.b2a_hex(bs_passwd.encode()).decode()
        data = f'{{"tls":{{"mode":"psk","details":{{"identity":"{endpoint}","key":"{psk}"}}}},"endpoint":"{endpoint}"}}'
        self.put('/security/clients/', data)
        ep = str([ord(n) for n in endpoint])
        key = str([ord(n) for n in passwd])
        content = '{"servers":{"0":{"binding":"U","defaultMinPeriod":1,"lifetime":86400,"notifIfDisabled":false,"shortId":1}},"security":{"1":{"bootstrapServer":false,"clientOldOffTime":1,"publicKeyOrId":' + ep + ',"secretKey":' + key + ',"securityMode":"PSK","serverId":1,"serverSmsNumber":"","smsBindingKeyParam":[],"smsBindingKeySecret":[],"smsSecurityMode":"NO_SEC","uri":"'+server_uri+'"}},"oscore":{},"toDelete":["/0","/1"]}'
        self.post(f'/bootstrap/{endpoint}', content)

    def delete_bs_device(self, endpoint: str):
        self.delete(f'/security/clients/{endpoint}')
        self.delete(f'/bootstrap/{endpoint}')
