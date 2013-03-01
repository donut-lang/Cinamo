/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
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
