/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include "../TestCommon.h"
#include <cinamo/Url.h>

namespace cinamo {
namespace url {

TEST(UrlTest, PercentDecodeTest)
{
	ASSERT_EQ("NOT_ENCODED", decodePercent("NOT_ENCODED"));
	ASSERT_EQ("test test", decodePercent("test%20test"));
	ASSERT_EQ("test PERCENT_ENCOD\r\nED", decodePercent("test%20%50%45%52%43%45%4e%54%5f%45%4e%43%4f%44%0d%0a%45%44"));
	ASSERT_EQ("test+test", decodePercent("test+test"));
	ASSERT_EQ("test++", decodePercent("test++"));
	ASSERT_EQ("\x20", decodePercent("%20"));
	ASSERT_EQ("\xff", decodePercent("%ff"));
}

TEST(UrlTest, PercentEncodeTest)
{
	ASSERT_EQ("NOT_ENCODED", encodePercent("NOT_ENCODED"));
	ASSERT_EQ("test%20test", encodePercent("test test"));
	ASSERT_EQ("test%20PERCENT_ENCOD%0D%0AED", encodePercent("test PERCENT_ENCOD\r\nED"));
	ASSERT_EQ("test+test", encodePercent("test+test"));
	ASSERT_EQ("%20", encodePercent("\x20"));
	ASSERT_EQ("%FF", encodePercent("\xff"));

	ASSERT_EQ("%E3%82%A6%E3%82%A3%E3%82%AD%E3%83%9A%E3%83%87%E3%82%A3%E3%82%A2", encodePercent("ウィキペディア"));
}

}}
