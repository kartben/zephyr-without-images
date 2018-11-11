#!/bin/bash
# Copyright (c) 2017 Linaro Limited
#
# SPDX-License-Identifier: Apache-2.0
#
# Author: Anas Nashif
#
# This script is run in CI and support both pull request and commit modes. So
# it can be used also on commits to the tree or on tags.
# The following options are supports:
# -p  start the script for pull requests
# -m  matrix node number, for example 3 on a 5 node matrix
# -M  total number of nodes in the matrix
# -b  base branch
# -r  the remote to rebase on
#
# The script can be run locally using for exmaple:
# ./scripts/ci/run_ci.sh -b master -r upstream  -p
source zephyr-env.sh

SANITYCHECK_OPTIONS=" --inline-logs --enable-coverage -N"
SANITYCHECK_OPTIONS_RETRY="${SANITYCHECK_OPTIONS} --only-failed --outdir=out-2nd-pass"
SANITYCHECK_OPTIONS_RETRY_2="${SANITYCHECK_OPTIONS} --only-failed --outdir=out-3nd-pass"
SANITYCHECK="${ZEPHYR_BASE}/scripts/sanitycheck"
MATRIX_BUILDS=1
MATRIX=1

while getopts ":pm:b:r:M:" opt; do
  case $opt in
    p)
      echo "Testing a Pull Request." >&2
      PULL_REQUEST=1
      ;;
    m)
      echo "Running on Matrix $OPTARG" >&2
      MATRIX=$OPTARG
      ;;
    M)
      echo "Running a matrix of $OPTARG slaves" >&2
      MATRIX_BUILDS=$OPTARG
      ;;
    b)
      echo "Base Branch: $OPTARG" >&2
      BRANCH=$OPTARG
      ;;
    r)
      echo "Remote: $OPTARG" >&2
      REMOTE=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      ;;
  esac
done

DOC_MATRIX=${MATRIX_BUILDS}
if [ -z "$BRANCH" ]; then
	echo "No base branch given"
	exit
fi

if [ -n "$PULL_REQUEST" ]; then
	git rebase $REMOTE/${BRANCH};
fi

if [ -n "$BRANCH" ]; then
	COMMIT_RANGE=$REMOTE/${BRANCH}..HEAD
	echo "Commit range:" ${COMMIT_RANGE}
else
	exit
fi

function build_btsim() {
	NRF_HW_MODELS_VERSION=`cat boards/posix/nrf52_bsim/hw_models_version`
	pushd . ;
	cd ${BSIM_COMPONENTS_PATH} ;
	git clone -b ${NRF_HW_MODELS_VERSION} https://github.com/BabbleSim/ext_NRF52_hw_models.git;
	cd /opt/bsim/ ;
	make everything -j 8;
	popd ;
}

function build_docs() {
    echo "- Building Documentation";
    make htmldocs
    if [ "$?" != "0" ]; then
      echo "Documentation build failed";
      exit 1;
    fi
    if [ -s doc/_build/doc.warnings ]; then
      echo " => New documentation warnings/errors";
      cp doc/_build/doc.warnings doc.warnings
    fi
    echo "- Verify commit message, coding style, doc build";
}

function get_tests_to_run() {
    ./scripts/ci/get_modified_tests.py --commits ${COMMIT_RANGE} > modified_tests.args;
    ./scripts/ci/get_modified_boards.py --commits ${COMMIT_RANGE} > modified_boards.args;

    if [ -s modified_boards.args ]; then
      ${SANITYCHECK} ${SANITYCHECK_OPTIONS} +modified_boards.args --save-tests test_file.txt || exit 1;
    fi
    if [ -s modified_tests.args ]; then
      ${SANITYCHECK} ${SANITYCHECK_OPTIONS} +modified_tests.args --save-tests test_file.txt || exit 1;
    fi
    rm -f modified_tests.args modified_boards.args;
}

# Build BT Simulator
test -z ${BSIM_OUT_PATH} || build_btsim

# Build Docs on matrix 5 in a pull request
if [ "${MATRIX}" = "${DOC_MATRIX}" -a -n "${PULL_REQUEST}" ]; then
	build_docs
	./scripts/ci/check-compliance.py --commits ${COMMIT_RANGE} || true;
fi

# In a pull-request see if we have changed any tests or board definitions
if [ -n "${PULL_REQUEST}" ]; then
	get_tests_to_run
fi

# Save list of tests to be run
${SANITYCHECK} ${SANITYCHECK_OPTIONS} --save-tests test_file.txt || exit 1

# Run a subset of tests based on matrix size
${SANITYCHECK} ${SANITYCHECK_OPTIONS} --load-tests test_file.txt --subset ${MATRIX}/${MATRIX_BUILDS}
if [ "$?" != 0 ]; then
	# let the host settle down
	sleep 10
	${SANITYCHECK} ${SANITYCHECK_OPTIONS_RETRY} || \
		( sleep 10; ${SANITYCHECK} ${SANITYCHECK_OPTIONS_RETRY}; )
fi

# cleanup
rm test_file.txt
