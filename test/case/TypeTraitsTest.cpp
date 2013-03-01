/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#include "../TestCommon.h"
#include <tarte/TypeTraits.h>

namespace tarte {

TEST(TypeTraitsTest, BasicTest){
	static_assert(
			std::is_same<
				decltype(::tarte::unary_function_return_type(&::isalnum)),
				decltype(::isalnum(1))
				>::value, "Could not return type.");
	static_assert(
			std::is_same<
				decltype(::tarte::unary_function_argument_type(&::isalnum)),
				int
				>::value, "Could not argument type.");
}

}
