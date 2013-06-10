/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include <cinamo/String.h>
#include <unicode/unistr.h>

namespace cinamo {


std::string trim(std::string const& str_)
{
	std::string tmp(str_);
	return trim(tmp);
}
std::string& trim(std::string& str_)
{
	UnicodeString str(UnicodeString::fromUTF8(str_));
	str.trim();
	str_.clear();
	str.toUTF8String(str_);
	return str_;
}


}
