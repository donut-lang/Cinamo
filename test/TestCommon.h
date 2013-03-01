/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#pragma once

#include <memory>
#include <iostream>

#include <tarte/Exception.h>
#include <tarte/Logger.h>

#include <gtest/gtest.h>
#include <tinyxml2.h>


using namespace tarte;

#define MATERIAL_DIR "__miscellaneous__/testfiles"

#define NULL_STREAM (*((std::ostream*)0))
static Logger log_trace(std::cout, Logger::TRACE_);
static Logger log_err(std::cout, Logger::ERROR_);

std::shared_ptr<tinyxml2::XMLDocument> parse(std::string const& str);

template <int... Args>
void static_debug(){
	static_assert(sizeof...(Args) < 0, "see type for compiler");
}

template <bool... Args>
void static_debug(){
	static_assert(sizeof...(Args) < 0, "see type for compiler");
}

template <typename... Args>
void static_debug(){
	static_assert(sizeof...(Args) < 0, "see type for compiler");
}

template<typename T, size_t N>
::testing::AssertionResult ArraysMatch(const T (&expected)[N], const T (&actual)[N])
{
	for (size_t i(0); i < N; ++i) {
		if (expected[i] != actual[i]) {
			return ::testing::AssertionFailure() << "array[" << i << "] ( = \"" << actual[i] << "\") != expected[" << i << "] ( = \"" << expected[i] << "\")";
		}
	}
	return ::testing::AssertionSuccess();
}
