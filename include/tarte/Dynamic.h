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
#include <typeinfo>
#include "Common.h"

namespace tarte {

std::string demangle(std::type_info const& info);

template <typename T>
std::string demangle(
		typename std::enable_if<!std::is_pointer<T>::value && !std::is_reference<T>::value >::type* = nullptr
)
{
	return demangle(typeid(T));
}

//ポインタが全部取れるまで再帰
template <typename T>
std::string demangle(typename std::enable_if<std::is_pointer<T>::value >::type* = nullptr)
{
	return demangle<typename std::remove_pointer<T>::type>();
}

//リファレンスが取れるまで再帰
template <typename T>
std::string demangle(typename std::enable_if<std::is_reference<T>::value >::type* = nullptr)
{
	return demangle<typename std::remove_reference<T>::type>();
}
template <typename T>
std::string demangle( T obj, typename std::enable_if<!std::is_pointer<T>::value >::type* = nullptr)
{
	return demangle(typeid(obj));
}

//ポインタを取り過ぎるとポリモルフィズムに対応できなくなっちゃうので再帰
template <typename T>
std::string demangle( T obj, typename std::enable_if<
		std::is_pointer<T>::value &&
		std::is_pointer<typename std::remove_pointer<T>::type >::value
			>::type* = nullptr)
{
	return demangle(*obj);
}

template <typename T>
std::string demangle( T obj, typename std::enable_if<
		std::is_pointer<T>::value &&
		!std::is_pointer<typename std::remove_pointer<T>::type >::value
			>::type* = nullptr)
{
	return demangle(typeid(*obj));
}

}
