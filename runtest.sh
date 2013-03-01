#! /bin/sh
# -*- coding: utf-8 -*-
# Tarte
#
# Copyright 2012-2013, PSI
# Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
# !! GPL is STRONGLY recommended !!
# see: http://donut-lang.org/license/

DIRNAME=$(cd $(dirname $0);pwd)
TEST_FILE="tarte_test"

function run() {
	PROG=$1/$TEST_FILE
	MODE=$2
	shift
	shift
	if [ -f $PROG ]; then
		echo "------------------------------------------------------------"
		echo "Running $MODE test"
		echo "------------------------------------------------------------"
		ECMD="$PROG $*"
		echo "%" $ECMD
		$ECMD
	else
		echo "not found: $PROG"
		return 1
	fi
}

run "$DIRNAME/build" "normal" $*
run "$DIRNAME/build/debug" "debug" $*
run "$DIRNAME/build/release" "release" $*
