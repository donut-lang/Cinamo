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
	UnicodeString str(UnicodeString::fromUTF8(str_));
	str.trim();
	std::string ret;
	str.toUTF8String(ret);
	return ret;
}


}
