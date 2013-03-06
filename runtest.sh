#! /bin/sh
# -*- coding: utf-8 -*-
# Cinamo
#
# Copyright 2012-2013, PSI

DIRNAME=$(cd $(dirname $0);pwd)
TEST_FILE="cinamo_test"

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
