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
	ASSERT_EQ("test PERCENT_ENCOD\r\nED", decodePercent("test %50%45%52%43%45%4e%54%5f%45%4e%43%4f%44%0d%0a%45%44"));
}

}}
