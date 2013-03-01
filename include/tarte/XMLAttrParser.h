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
#include <tinyxml2.h>
#include "Common.h"

#define DEF_OVERLOD(Klass)\
template <> void parseAttr(std::string const& name, Klass& ptr, Klass const& def, tinyxml2::XMLElement* elm)

namespace tarte {
namespace xml {

template <typename T> void parseAttr(std::string const& name, T& ptr, const T& def, tinyxml2::XMLElement* elm);
DEF_OVERLOD(std::string);
DEF_OVERLOD(float);
DEF_OVERLOD(int);
DEF_OVERLOD(unsigned int);
DEF_OVERLOD(bool);

}}

#undef DEF_OVERLOD
