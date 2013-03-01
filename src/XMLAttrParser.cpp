/**
 * Tarte
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
