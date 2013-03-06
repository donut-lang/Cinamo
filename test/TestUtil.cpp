/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include "TestCommon.h"

std::shared_ptr<tinyxml2::XMLDocument> parse(std::string const& str)
{
	std::shared_ptr<tinyxml2::XMLDocument> d(new tinyxml2::XMLDocument);
	d->Parse(str.c_str(), str.size());
	return d;
}

