/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include <gtest/gtest.h>
#include <unicode/unistr.h>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	const int r = RUN_ALL_TESTS();
	return r;
}
