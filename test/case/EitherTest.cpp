/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include "../TestCommon.h"
#include <cinamo/Base64.h>
#include <cinamo/functional/Either.h>

#include <cfloat>
#include <cmath>

namespace cinamo {

TEST(EitherTest, BasicTest)
{
	constexpr Either<int, int> i = Right<int, int>(10);
	auto r = (i >>= [](int x)->Either<int, int>{return Right<int,int>(x+190);});

	ASSERT_TRUE(r.isRight);
	ASSERT_FALSE(r.isLeft);
	ASSERT_EQ(r.answer(), 200);
}

}
