/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include "Common.h"
#include <cfloat>
#include <climits>

#define TARTE_IOS (defined(__IPHONE_OS_VERSION_MIN_REQUIRED))

#define TARTE_LINUX (defined(__linux__) || defined(__linux) || defined(__gnu_linux__) || defined(linux))
#define TARTE_WINDOWS (defined(WIN32) || defined(WIN64) || defined(__WIN32__) || defined(__WIN64__))
#define TARTE_ANDROID (defined(ANDROID))

#define HAVE_LONG_DOUBLE (!TARTE_ANDROID && defined(LDBL_MAX))
#define HAVE_LONG_LONG (!TARTE_ANDROID && defined(LLONG_MAX))

#if TARTE_WINDOWS
#define IS_BIG_ENDIAN 0
#else
#include <endian.h>
#define IS_BIG_ENDIAN (BYTE_ORDER == BIG_ENDIAN)
#endif

