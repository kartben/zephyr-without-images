/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2015 Runtime Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>

#include "fcb.h"
#include "fcb_priv.h"

static struct flash_area *
fcb_new_area(struct fcb *fcb, int cnt)
{
	struct flash_area *fa;
	struct flash_area *rfa;
	int i;

	rfa = NULL;
	i = 0;
	fa = fcb->f_active.fe_area;
	do {
		fa = fcb_getnext_area(fcb, fa);
		if (!rfa) {
			rfa = fa;
		}
		if (fa == fcb->f_oldest) {
			return NULL;
		}
	} while (i++ < cnt);
	return rfa;
}

/*
 * Take one of the scratch blocks into use, if at all possible.
 */
int
fcb_append_to_scratch(struct fcb *fcb)
{
	struct flash_area *fa;
	int rc;

	fa = fcb_new_area(fcb, 0);
	if (!fa) {
		return FCB_ERR_NOSPACE;
	}
	rc = fcb_sector_hdr_init(fcb, fa, fcb->f_active_id + 1);
	if (rc) {
		return rc;
	}
	fcb->f_active.fe_area = fa;
	fcb->f_active.fe_elem_off = sizeof(struct fcb_disk_area);
	fcb->f_active_id++;
	return FCB_OK;
}

int
fcb_append(struct fcb *fcb, u16_t len, struct fcb_entry *append_loc)
{
	struct fcb_entry *active;
	struct flash_area *fa;
	u8_t tmp_str[2];
	int cnt;
	int rc;

	cnt = fcb_put_len(tmp_str, len);
	if (cnt < 0) {
		return cnt;
	}
	cnt = fcb_len_in_flash(fcb, cnt);
	len = fcb_len_in_flash(fcb, len) + fcb_len_in_flash(fcb, FCB_CRC_SZ);

	rc = k_mutex_lock(&fcb->f_mtx, K_FOREVER);
	if (rc) {
		return FCB_ERR_ARGS;
	}
	active = &fcb->f_active;
	if (active->fe_elem_off + len + cnt > active->fe_area->fa_size) {
		fa = fcb_new_area(fcb, fcb->f_scratch_cnt);
		if (!fa || (fa->fa_size <
			sizeof(struct fcb_disk_area) + len + cnt)) {
			rc = FCB_ERR_NOSPACE;
			goto err;
		}
		rc = fcb_sector_hdr_init(fcb, fa, fcb->f_active_id + 1);
		if (rc) {
			goto err;
		}
		fcb->f_active.fe_area = fa;
		fcb->f_active.fe_elem_off = sizeof(struct fcb_disk_area);
		fcb->f_active_id++;
	}

	rc = flash_area_write(active->fe_area, active->fe_elem_off, tmp_str,
			      cnt);
	if (rc) {
		rc = FCB_ERR_FLASH;
		goto err;
	}
	append_loc->fe_area = active->fe_area;
	append_loc->fe_elem_off = active->fe_elem_off;
	append_loc->fe_data_off = active->fe_elem_off + cnt;

	active->fe_elem_off = append_loc->fe_data_off + len;

	k_mutex_unlock(&fcb->f_mtx);

	return FCB_OK;
err:
	k_mutex_unlock(&fcb->f_mtx);
	return rc;
}

int
fcb_append_finish(struct fcb *fcb, struct fcb_entry *loc)
{
	int rc;
	u8_t crc8;
	off_t off;

	rc = fcb_elem_crc8(fcb, loc, &crc8);
	if (rc) {
		return rc;
	}
	off = loc->fe_data_off + fcb_len_in_flash(fcb, loc->fe_data_len);

	rc = flash_area_write(loc->fe_area, off, &crc8, sizeof(crc8));
	if (rc) {
		return FCB_ERR_FLASH;
	}
	return 0;
}
