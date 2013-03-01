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

#include <string>
#include <vector>
#include "Common.h"
#include "Platform.h"
#include "internal/FileSystem.h"

namespace tarte {
namespace file {

template <typename T, typename... Args>
constexpr typename internal::FileConstants<T>::string_type join(const T& a, Args const&... left)
{
	return typename internal::FileConstants<T>::string_type(a)+internal::FileConstants<T>::Sep+join(left...);
}

std::vector<std::string> enumFiles(std::string const& dir, bool recursive=false);
std::string readAsString(std::istream& stream);
std::string readAsString(std::string const& fname);

}}
