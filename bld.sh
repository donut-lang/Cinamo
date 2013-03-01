#! /bin/bash
# -*- coding: utf-8 -*-
# Tarte
#
# Copyright 2012-2013, PSI
# Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
# !! GPL is STRONGLY recommended !!
# see: http://donut-lang.org/license/

if [ -z $PYTHON ]; then
	PYTHON=python
fi

DIRNAME=$(cd $(dirname $0);pwd)
if [ -z $BUILDDIR ]; then
	BUILDDIR=$DIRNAME/build
fi

function detectCompiler() {
	echo "------------------------------------------------------------"
	echo "detecting compiler"
	echo "------------------------------------------------------------"
	CLANG_FOUND=0
	if which clang++ > /dev/null 2>&1; then
		echo "[clang++] found."
		CLANG_FOUND=1
	else
		echo "[clang++] not found."
	fi

	CCACHE_FOUND=0
	if which ccache > /dev/null 2>&1; then
		echo "[ccache] found."
		CCACHE_FOUND=1
	else
		echo "[cchache] not found."
	fi

	if [ $CLANG_FOUND -eq 1 ];then
		export set CC='clang'
		export set CXX='clang++'
	elif [ $CCACHE_FOUND -eq 1 ] ;then
		export set CC='ccache gcc'
		export set CXX='ccache g++'
	fi
	echo "CC  =" $CC
	echo "CXX =" $CXX
	echo "------------------------------------------------------------"
}

function runConfig() {
	echo "------------------------------------------------------------"
	echo "cleaning"
	echo "------------------------------------------------------------"
	echo "%" $PYTHON waf distclean
	$PYTHON waf distclean
	echo "------------------------------------------------------------"
	echo "configureing"
	echo "------------------------------------------------------------"
	if [ "$MSYSTEM" = "MINGW32" -o "$OS" = "Windows_NT" ] ; then
		CONFIGURE_CMD="$PYTHON waf configure --out $BUILDDIR $CONF_OPT"
	else
		CONFIGURE_CMD="$PYTHON waf configure --out $BUILDDIR $CONF_OPT"
	fi
	echo "%" $CONFIGURE_CMD
	$CONFIGURE_CMD
	res=$?
	echo "------------------------------------------------------------"
	return $res
}

function ensureConfigure() {
	if test -d $BUILDDIR && $PYTHON ./waf list > /dev/null 2>&1
	then
		echo "configured"
		return 0
	fi
	echo "not configured"
	detectCompiler
	runConfig
}

function parse() {
	if echo "$1" | grep -- "-.*" > /dev/null 2>&1; then #オプションである
		return 1
	elif [ "$1" = "debug" ] ; then
		MODE=$1
	elif [ "$1" = "release" ] ; then
		MODE=$1
	elif [ "$1" = "build" ] ; then
		TARGET=$1
	elif [ "$1" = "clean" ] ; then
		TARGET=$1
	elif [ "$1" = "install" ] ; then
		TARGET=$1
	elif [ "$1" = "uninstall" ] ; then
		TARGET=$1
	elif [ "$1" = "test" ] ; then
		LAUNCH="test"
	elif [ ! -z "$1" ]; then
		LAUNCH="custom"
		return 1
	fi
	return 0
}

# parsing command line
LAUNCH="normal"
parse $1 && shift
parse $1 && shift
if [ -z "$MODE" ]; then
	MODE="debug"
fi
if [ -z "$TARGET" ]; then
	TARGET="build"
fi

#launching main task
if [ $LAUNCH = "normal" ]; then
	WAF_CMD="$PYTHON ./waf --out $BUILDDIR ${TARGET}_${MODE} $*"
	ensureConfigure
	if [ $? -eq 0 ]; then
		echo "============================================================"
		echo "Normal launch"
		echo "mode   =" $MODE
		echo "target =" $TARGET
		echo "============================================================"
		echo "%" $WAF_CMD
		$WAF_CMD
	else
		echo "build faled to configure."
		exit 1
	fi
elif [ $LAUNCH = "test" ] ;then
	echo "============================================================"
	echo "Run test"
	echo "============================================================"
	if [ -e runtest.sh ] ;then 
		echo "%" sh runtest.sh
		sh runtest.sh
	else
		echo "runtest.sh not found."
		exit 1
	fi
elif [ $LAUNCH = "custom" ] ;then
	echo "============================================================"
	echo "Custom launch"
	echo "============================================================"
	WAF_CMD="$PYTHON ./waf --out $BUILDDIR $*"
	echo "%" $WAF_CMD
	$WAF_CMD
fi
