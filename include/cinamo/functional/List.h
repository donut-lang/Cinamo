/* coding: utf-8 */
/**
 * CppMonad
 *
 * Copyright 2013, psi
 */

/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2013, psi
 */
#pragma once
#include <array>
#include <initializer_list>
#include "../TypeTrans.h"

namespace cinamo {

template <typename A, size_t len>
class List {
private:
	std::array<A, len> spirit;
public:
	template <typename... Args>
	constexpr List(Args... args):spirit( (std::array<A, len>{{ args... }}) ){
	}
private:
	template <typename R, size_t n_, typename F, typename... Args>
	constexpr R call_(typename std::enable_if<(n_ == 0)>::type*,F f, Args... args)
	{
		return f(args...);
	}
	template <typename R, size_t n_, typename F, typename... Args>
	constexpr R call_(typename std::enable_if<(n_ > 0)>::type*, F f, Args... args)
	{
		return call_<R,n_-1,F>(nullptr, f, spirit[n_-1], args...);
	}
	template <typename R, typename... Args>
	constexpr R call_proxy(std::function<R(Args...)> f)
	{
		return call_<R, len>(nullptr, f);
	}
public:
	template <typename F>
	constexpr auto call(F f) -> decltype(this->call_proxy(makeFunctor(f))) const{
		return this->call_proxy(makeFunctor(f));
	}
};

template <typename A, typename... Left>
constexpr List<A, sizeof...(Left)+1> toList(A const& a, Left... l){
	return List<A, sizeof...(Left)+1>({a, l...});
}


}


