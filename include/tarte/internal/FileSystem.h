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

#include "../Platform.h"
#include <string>
#include <set>

namespace tarte {
namespace file {

namespace internal {

template <class String>
struct FileConstants ;

#if TARTE_WINDOWS
#define TARTE_FILE_SEP "\\"
#define TARTE_FILE_SEPW L"\\"
#else
#define TARTE_FILE_SEP "/"
#define TARTE_FILE_SEPW L"/"
#endif

#define STRING_INNER \
typedef char* char_type;\
typedef const char* const_char_type;\
typedef std::string string_type;\
typedef const std::string const_string_type;\
static constexpr const_char_type Sep = TARTE_FILE_SEP;\
static constexpr const_char_type CurrentDir = ".";\
static constexpr const_char_type ParentDir = "..";

#define WSTRING_INNER \
typedef wchar_t* char_type;\
typedef const wchar_t* const_char_type;\
typedef std::wstring string_type;\
typedef const std::wstring const_string_type;\
static constexpr const_char_type Sep = TARTE_FILE_SEPW;\
static constexpr const_char_type CurrentDir = L".";\
static constexpr const_char_type ParentDir = L"..";

template<> struct FileConstants<std::string>{ STRING_INNER };
template<> struct FileConstants<std::wstring> { WSTRING_INNER };

template<> struct FileConstants<char> { STRING_INNER };
template<> struct FileConstants<wchar_t> { WSTRING_INNER };

template<> struct FileConstants<char*> { STRING_INNER };
template<> struct FileConstants<wchar_t*> { WSTRING_INNER };

template<> struct FileConstants<const char*> { STRING_INNER };
template<> struct FileConstants<const wchar_t*> { WSTRING_INNER };

template<std::size_t N> struct FileConstants<char[N]> { STRING_INNER };
template<std::size_t N> struct FileConstants<wchar_t [N]> { WSTRING_INNER };

#undef STRING_INNER
#undef WSTRING_INNER
#undef TARTE_FILE_SEP
#undef TARTE_FILE_SEPW

}

template <typename T>
constexpr const T& join(const T& a)
{
	return a;
}

}}
