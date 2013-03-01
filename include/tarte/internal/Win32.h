/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
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
