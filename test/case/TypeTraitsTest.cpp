/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include "../TestCommon.h"
#include <cinamo/TypeTraits.h>

namespace cinamo {

TEST(TypeTraitsTest, BasicTest){
	static_assert(
			std::is_same<
				decltype(::cinamo::unary_function_return_type(&::isalnum)),
				decltype(::isalnum(1))
				>::value, "Could not return type.");
	static_assert(
			std::is_same<
				decltype(::cinamo::unary_function_argument_type(&::isalnum)),
				int
				>::value, "Could not argument type.");
}

}
