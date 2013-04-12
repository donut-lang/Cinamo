/* coding: utf-8 */
/**
 * CppMonad
 *
 * Copyright 2013, psi
 */

/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2013, psi
 */
#pragma once
#include <initializer_list>

namespace cinamo {

template <typename A, size_t len>
class List {
private:
	A const spirit[len];
public:
	constexpr List(A const (&list)[len]):spirit(list){
	}
};

}


