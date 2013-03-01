/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 */

#include <cstdarg>
#include <string>
#include <vector>

#pragma once

namespace tarte {
namespace base64 {

std::string encode( std::vector<char> const& data );
std::string encode( std::string const& data );
std::string encode( const char* data, const std::size_t length);
std::vector<char> decode( std::string const& str );
std::string decodeAsString( std::string const& str );

}}
