/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include <cstdarg>
#include <string>
#include <vector>

#pragma once

namespace cinamo {
namespace base64 {

/**
 * vectorのデータをbase64にエンコードする。
 */
std::string encode( std::vector<char> const& data );

/**
 * stringをバイナリデータと見立ててbase64にエンコードする
 */
std::string encode( std::string const& data );

/**
 * 任意のバイナリデータをbase64にエンコードする。
 */
std::string encode( const char* data, const std::size_t length);

/**
 * base64データを元のバイナリデータに戻す。
 */
std::vector<char> decode( std::string const& str );

/**
 * 型を指定してbase64デコードする。
 */
template <typename T> T decode( std::string const& str );

template <> inline std::vector<char> decode( std::string const& str ) {
	return decode(str);
}
template <> inline std::string decode( std::string const& str ) {
	const std::vector<char> dat(decode(str));
	return std::string(dat.data(), dat.size());
}

}}
