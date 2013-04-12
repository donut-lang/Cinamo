/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include "../TestCommon.h"
#include <cinamo/functional/Parser.h>

namespace cinamo {

TEST(ParserTest, NumberTest)
{
	using namespace cinamo::parser;

	constexpr auto b = number();
	constexpr auto ans = (b("012133afg")).answer();
	static_assert(ans.first.begin == 0, "Failed to parse");
	static_assert(ans.first.end == 6, "Failed to parse");
}
TEST(ParserTest, SelectCombineTest)
{
	using namespace cinamo::parser;

	constexpr auto b = ((loop<digit>()) || (loop<alphabet>())) >> (loop<alphabet>());
	constexpr auto ans = (b("0aaaaa")).answer();
	static_assert(ans.first.begin == 0, "Failed to parse");
	static_assert(ans.first.end == 6, "Failed to parse");
}

}
