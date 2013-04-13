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
	static constexpr R call_(typename std::enable_if<(n_ == 0)>::type*,std::array<A, len> const& spirit, F f, Args... args)
	{
		return f(args...);
	}
	template <typename R, size_t n_, typename F, typename... Args>
	static constexpr R call_(typename std::enable_if<(n_ > 0)>::type*, std::array<A, len> const& spirit, F f, Args... args)
	{
		return call_<R,n_-1,F>(nullptr, spirit, f, spirit[n_-1], args...);
	}
	template <typename R, typename... Args>
	static constexpr R call_proxy(std::array<A, len> const& spirit, std::function<R(Args...)> f)
	{
		return call_<R, len>(nullptr, spirit, f);
	}
public:
	template <typename F>
	constexpr auto call(F f) -> decltype(call_proxy(spirit, makeFunctor(f))) const{
		return call_proxy(spirit, makeFunctor(f));
	}
};

template <typename A, typename... Left>
constexpr List<A, sizeof...(Left)+1> toList(A const& a, Left... l){
	return List<A, sizeof...(Left)+1>({a, l...});
}


}


