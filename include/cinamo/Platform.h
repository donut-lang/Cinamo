/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include "Common.h"
#include <cfloat>
#include <climits>

#ifdef CINAMO_EMBEDDED

#ifndef HAVE_ICU
#define HAVE_ICU 0
#endif

#ifndef HAVE_BOOST
#define HAVE_BOOST 0
#endif

#endif

#ifndef CINAMO_EMBEDDED
#include <config.h>
#endif

#define CINAMO_IOS (defined(__IPHONE_OS_VERSION_MIN_REQUIRED))

#define CINAMO_LINUX (defined(__linux__) || defined(__linux) || defined(__gnu_linux__) || defined(linux))
#define CINAMO_WINDOWS (defined(WIN32) || defined(WIN64) || defined(__WIN32__) || defined(__WIN64__))
#define CINAMO_ANDROID (defined(__ANDROID__))

#define HAVE_FLOAT (defined(FLT_MAX))
#define HAVE_DOUBLE (defined(DBL_MAX))
#define HAVE_LONG_DOUBLE (defined(LDBL_MAX))
#define HAVE_STRTOLD (!CINAMO_ANDROID && HAVE_LONG_DOUBLE)

#define HAVE_CHAR (defined(CHAR_MAX))
#define HAVE_UCHAR (defined(UCHAR_MAX))
#define HAVE_SCHAR (defined(SCHAR_MAX))

#define HAVE_SHORT (defined(SHRT_MAX))
#define HAVE_USHORT (defined(USHRT_MAX))

#define HAVE_LONG (defined(LONG_MAX))
#define HAVE_ULONG (defined(ULONG_MAX))

#define HAVE_LONGLONG (defined(LLONG_MAX))
#define HAVE_ULONGLONG (defined(ULLONG_MAX))
#define HAVE_STRTOLL (HAVE_LONGLONG)
#define HAVE_STRTOULL (HAVE_ULONGLONG)

#if CINAMO_WINDOWS
#define IS_BIG_ENDIAN 0
#else

namespace {
#include <endian.h>
#define IS_BIG_ENDIAN (BYTE_ORDER == BIG_ENDIAN)
}

#endif

