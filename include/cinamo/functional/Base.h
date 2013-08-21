/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#pragma once

namespace cinamo {

struct Unit final{
	operator void(){
		return void();
	}
	constexpr bool operator==(Unit const&) { return true; }
	constexpr bool operator!=(Unit const&) { return false; }
};

}
