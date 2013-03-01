/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#include "TestCommon.h"

std::shared_ptr<tinyxml2::XMLDocument> parse(std::string const& str)
{
	std::shared_ptr<tinyxml2::XMLDocument> d(new tinyxml2::XMLDocument);
	d->Parse(str.c_str(), str.size());
	return d;
}

