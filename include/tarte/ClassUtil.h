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
#include <cstddef>
#include "Common.h"
#define DISABLE_COPY_AND_ASSIGN(klass)\
	klass(klass const& other) = delete;\
	klass(klass&& other) = delete;\
	klass& operator=(klass const& other) = delete;\
	klass& operator=(klass&& other) = delete;

#define DEFAULT_COPY_AND_ASSIGN(klass)\
public:\
	klass(klass const& other) = default;\
	klass(klass&& other) = default;\
	klass& operator=(klass const& other) = default;\
	klass& operator=(klass&& other) = default;

#define STACK_OBJECT(Klass)\
	void* operator new(std::size_t) = delete;\
	void operator delete(void*) = delete;

//-----------------------------------------------------------------------------

#define DEFINE_MEMBER_CONST(rscope, type, name)\
private:\
	type const name##_;\
rscope:\
	inline type const& name() const noexcept{return name##_;}

#define DEFINE_MEMBER_REF(rscope, type, name)\
private:\
	type& name##_;\
rscope:\
	inline type& name() const noexcept{return name##_;}

#define DEFINE_MEMBER(rscope, wscope, type, name)\
private:\
	type name##_;\
rscope:\
	inline type const& name() const noexcept{return name##_;}\
wscope:\
	inline void name(type const& val){name##_ = val;}

#define DEFINE_CONTAINER(rscope, wscope, ctype, name)\
private:\
	ctype name##_;\
rscope:\
	inline ctype const& name() const noexcept{return name##_;}\
wscope:\
	inline ctype& name() noexcept{return name##_;}\
	inline void name(ctype const& val){name##_ = val;}

#define DEFINE_MEMBER_LITERAL(rscope, wscope, type, name)\
private:\
	type name##_;\
rscope:\
	inline constexpr type const& name() const noexcept{return name##_;}\
wscope:\
	inline void name(type const& val){name##_ = val;}
