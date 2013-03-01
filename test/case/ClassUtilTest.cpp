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
#include <tarte/ClassUtil.h>

namespace tarte {

class Sample {
	DEFINE_MEMBER(public, public, int, val)
	DEFINE_MEMBER(public, public, std::string, str)
public:
	Sample(int v, std::string const& str):val_(v), str_(str){}
};

TEST(ClassUtilTest, DefineMemberLiteralGetterSetterTest)
{
	Sample s(0,"");
	ASSERT_EQ(0, s.val());
	s.val(0);
	ASSERT_EQ(0, s.val());
	s.val(1);
	ASSERT_EQ(1, s.val());
}

TEST(ClassUtilTest, ConstDefineMemberLiteralGetterSetterTest)
{
	const Sample s(012,"");
	ASSERT_EQ(012, s.val());
}

TEST(ClassUtilTest, DefineMemberLiteralReferenceTest)
{
	Sample s(0,"");
	ASSERT_EQ(0, s.val());
	static_assert(std::is_same<decltype(s.val()), int const&>::value, "oops. overload failed.");
}

TEST(ClassUtilTest, ConstDefineMemberLiteralReferenceTest)
{
	const Sample s(0,"");
	ASSERT_EQ(0, s.val());
	static_assert(std::is_same<decltype(s.val()), int const&>::value, "oops. overload failed.");
}

}
