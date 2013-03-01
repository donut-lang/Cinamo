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
#include <utility>
#include <functional>
#include "Common.h"

namespace tarte {

template <typename T, typename U>
struct PairCompare : public std::binary_function<std::pair<T,U>,std::pair<T,U>,bool>{
	bool operator()(T const& a, std::pair<T,U> const& b){
		return std::less<T>()(a, b.first);
	}
	bool operator()(std::pair<T,U> const& a, std::pair<T,U> const& b){
		return std::less<T>()(a.first, b.first);
	}
	bool operator()(std::pair<T,U> const& a, T const& b){
		return std::less<T>()(a.first, b);
	}
};

template <typename T, typename U>
struct PairEq : public std::unary_function<std::pair<T,U>,bool>{
private:
	T const& t_;
public:
	PairEq(T const& t):t_(t){}
	bool operator()(T const& a){
		return a == t_;
	}
	bool operator()(std::pair<T,U> const& a){
		return a.first == t_;
	}
};

}

#undef DEF_OVERLOD
