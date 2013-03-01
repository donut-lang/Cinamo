/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#include <gtest/gtest.h>
#include <unicode/unistr.h>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	const int r = RUN_ALL_TESTS();
	return r;
}
