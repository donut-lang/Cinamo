/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#include <string>
#include <tarte/XMLAttrParser.h>
#include <tarte/String.h>

namespace tarte {
namespace xml {

#define PARSE_AS(type)\
template <> void parseAttr<type>(std::string const& name, type& v, type const& def, tinyxml2::XMLElement* elm)\
{\
	bool res=false;\
	if(const char* attr = elm->Attribute(name.c_str())){\
		v = parseAs<type>(attr, &res);\
		if(res) {\
			return;\
		}\
	}\
	v = def;\
}

PARSE_AS(int);
PARSE_AS(unsigned int);
PARSE_AS(float);
PARSE_AS(bool);

#undef PARSE_AS

template <> void parseAttr<std::string>(std::string const& name, std::string& v, std::string const& def, tinyxml2::XMLElement* elm)
{
	if(const char* attr = elm->Attribute(name.c_str())){
		v = attr;
	}else{
		v = def;
	}
}

}}
