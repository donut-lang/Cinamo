#! /bin/sh
# -*- coding: utf-8 -*-
# Cinamo
#
# Copyright 2012-2013, PSI

DIRNAME=$(cd $(dirname $0);pwd)
TEST_FILE="cinamoTest"

IS_DEBUG=0

for arg in $*; do
	if [ $arg == "debug" ]; then
		IS_DEBUG=1
	fi
done

function run() {
	PROG=$1/$TEST_FILE
	MODE=$2
	shift
	shift
	if [ -f $PROG ]; then
		echo "------------------------------------------------------------"
		echo "Running $MODE test"
		echo "------------------------------------------------------------"
		if [ 0 -eq $IS_DEBUG ]; then
			ECMD="$PROG $*"
			echo "%" $ECMD
			$ECMD
		else
			ECMD="gdb --args $PROG $*"
			echo "%" $ECMD
			$ECMD
		fi
	else
		echo "not found: $PROG"
		return 1
	fi
}

run "$DIRNAME/build" "normal" $*
run "$DIRNAME/build/debug" "debug" $*
run "$DIRNAME/build/release" "release" $*
