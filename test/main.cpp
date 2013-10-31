/* coding: utf-8 */
/**
<<<<<<< HEAD
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
=======
 * TestEntryPoint
 *
 * Copyright 2013, psi
 */

#include <gtest/gtest.h>
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

>>>>>>> __template__/master
