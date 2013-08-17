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
#include "config.h"
#endif

#define CINAMO_IOS (defined(__IPHONE_OS_VERSION_MIN_REQUIRED))

#define CINAMO_LINUX (defined(__linux__) || defined(__linux) || defined(__gnu_linux__) || defined(linux))
#define CINAMO_WINDOWS (defined(WIN32) || defined(WIN64) || defined(__WIN32__) || defined(__WIN64__))
#define CINAMO_ANDROID (defined(ANDROID))

#define HAVE_LONG_DOUBLE (!CINAMO_ANDROID && defined(LDBL_MAX))
#define HAVE_LONG_LONG (!CINAMO_ANDROID && defined(LLONG_MAX))

#if CINAMO_WINDOWS
#define IS_BIG_ENDIAN 0
#else
#include <endian.h>
#define IS_BIG_ENDIAN (BYTE_ORDER == BIG_ENDIAN)
#endif

