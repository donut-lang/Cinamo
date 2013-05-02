/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include "../TestCommon.h"
#include <cinamo/Matrix.h>

#include <cfloat>
#include <cmath>

namespace cinamo {

TEST(MatrixTest, InitializeTest)
{
	Mat<3,3> const mat = {
			1.0,2.0,3.0,
			4.0,5.0,6.0,
			7.0,8.0,9.0};
	ASSERT_FLOAT_EQ( 1.0, mat(0,0) );
	ASSERT_FLOAT_EQ( 6.0, mat(1,2) );
}
TEST(MatrixTest, MulTest)
{
	Mat<3,3> const m = {
			1.0, 1.0, 1.0,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0,
	};
	Mat<3,3> const mat = {
			1.0,2.0,3.0,
			4.0,5.0,6.0,
			7.0,8.0,9.0};
	auto m2 = mat * m;
	ASSERT_FLOAT_EQ( 1.0, m2(0,0) );
	ASSERT_FLOAT_EQ( 1.0, m2(0,1) );
	ASSERT_FLOAT_EQ( 1.0, m2(0,2) );

	ASSERT_FLOAT_EQ( 4.0, m2(1,0) );
	ASSERT_FLOAT_EQ( 4.0, m2(1,1) );
	ASSERT_FLOAT_EQ( 4.0, m2(1,2) );

	ASSERT_FLOAT_EQ( 7.0, m2(2,0) );
	ASSERT_FLOAT_EQ( 7.0, m2(2,1) );
	ASSERT_FLOAT_EQ( 7.0, m2(2,2) );
}

}
