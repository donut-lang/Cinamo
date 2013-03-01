/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#pragma once

#include "../Platform.h"
#if TARTE_WINDOWS
#include <Windows.h>
#include <string>

namespace tarte {
namespace internal {
namespace win32 {

std::wstring toUTF16(std::string const& str);
std::string toUTF8(std::wstring const& str);

}}}

#endif
