/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#include <cstdarg>
#include <string>
#include <vector>
#include "Common.h"

#pragma once
/* FIXME: さきゅばすから取ってきた */

namespace tarte {

std::string format(std::string const& fmt, ...);
std::string formatv(std::string const& fmt, va_list args);
#define TOSTR_DEF(type) std::string toString(type const& val, int radix=10);
TOSTR_DEF(int);
TOSTR_DEF(unsigned int);
TOSTR_DEF(long int);
TOSTR_DEF(unsigned long int);
TOSTR_DEF(long long int);
TOSTR_DEF(unsigned long long int);
#undef TOSTR_DEF
std::string toString(const float val);
std::string toString(const double val);
std::string toString(const bool val);
std::string toLower(std::string const& str);
std::string toUpper(std::string const& str);
std::string join(std::vector<std::string> const& lst);
std::string join(std::vector<std::string> const& lst, std::string const& sep);
std::size_t matchString(std::string const& a, std::string const& b);
std::string randomString(std::size_t len);

std::vector<std::string> breakChar(std::string const& str_);

template <typename T>
T parseAs(std::string const& str, int radix, bool* succeed=nullptr);
template <typename T>
T parseAs(std::string const& str, bool* succeed=nullptr);

std::string decodePercent(std::string const& str);
void split(std::string const& str, std::string const& sep, std::vector<std::string>& list);
void split(std::string const& str, const std::string* sep, size_t n, std::vector<std::string>& list);
template <size_t N>
void split(std::string const& str, const std::string (&sep)[N], std::vector<std::string>& list)
{
	split(str, sep, N, list);
}
void splitSpace(std::string const& str, std::vector<std::string>& list);
void splitLine(std::string const& str, std::vector<std::string>& list);
bool startsWith(std::string const& target, std::string const& prefix);
bool endsWith(std::string const& target, std::string const& suffix);

}
