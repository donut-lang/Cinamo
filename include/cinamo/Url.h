/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include <string>
#include "Common.h"

#pragma once
namespace cinamo {
namespace url {

std::string decodePercent(std::string const& str);
std::string encodePercent(std::string const& str);

}}
