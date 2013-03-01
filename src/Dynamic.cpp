/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#include <tarte/Dynamic.h>

#include <cxxabi.h>

namespace tarte {


std::string demangle(std::type_info const& info)
{
	int status;
	return abi::__cxa_demangle(info.name(), 0, 0, &status);
}

}
