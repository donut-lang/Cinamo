/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include <string>

#pragma once
namespace cinamo {

template <typename T>
T parseAs(std::string const& str, int radix, T const& default_)
{
	T result;
	if( tryParseAs<T>(str, radix, result) ){
		return result;
	}else{
		return default_;
	}
}
template <typename T>
T parseAs(std::string const& str, T const& default_)
{
	T result;
	if( tryParseAs<T>(str, result) ){
		return result;
	}else{
		return default_;
	}
}

}
