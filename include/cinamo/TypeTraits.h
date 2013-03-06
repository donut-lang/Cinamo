/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include "Common.h"
#include <functional>

namespace cinamo {

namespace internal {
	template <typename Func>
	struct UnaryFunctionType {
		template <typename R, typename A>
		static auto f(std::function<R(A)>) -> A;
		template <typename R, typename A>
		static auto f(R(*)(A)) -> A;
		template <typename R, typename A>
		static auto g(std::function<R(A)>) -> R;
		template <typename R, typename A>
		static auto g(R(*)(A)) -> R;
		typedef decltype( f( std::declval<Func>()) ) argument_type;
		typedef decltype( g( std::declval<Func>()) ) return_type;
	};
}

template <typename R>
typename internal::UnaryFunctionType<R>::return_type unary_function_return_type(R);

template <typename R>
typename internal::UnaryFunctionType<R>::argument_type unary_function_argument_type(R);

}
