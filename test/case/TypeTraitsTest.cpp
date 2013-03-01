/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
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
