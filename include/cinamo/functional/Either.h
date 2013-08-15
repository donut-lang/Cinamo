/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2013, psi
 */
#pragma once

#include <utility>
#include <type_traits>
#include "Base.h"
#include "Ident.h"
#include "Maybe.h"

namespace cinamo {

namespace either_innenr{
class LeftEnumT;
class RightEnumT;
class ConstexprLeftEnumT;
class ConstexprRightEnumT;
}
template <typename E, typename A, typename U=void> class Either;
template <typename E, typename A>
Either<E,A> Left(E const& e) {
	return Either<E,A>(e, static_cast<either_innenr::LeftEnumT*>(nullptr));
}

template <typename E, typename A>
Either<E,A> Right(A const& a){
	return Either<E,A>(a, static_cast<either_innenr::RightEnumT*>(nullptr));
}

template <typename E, typename A, typename U>
class Either {
public:
	bool const isLeft;
	bool const isRight;
private:
	union {
		E const error_;
		A const answer_;
	};
public:
	Either(E const& e, either_innenr::LeftEnumT*)
	:isLeft(true)
	,isRight(false)
	,error_(e)
	{}
	Either(A const& a, either_innenr::RightEnumT*)
	:isLeft(false)
	,isRight(true)
	,answer_(a)
	{}
	Either(Either<E,A> const& e)
	:isLeft(e.isLeft)
	,isRight(e.isRight)
	{
		if( isLeft ) {
			new (const_cast<E*>(static_cast<const E*>(&this->error_))) E( (e.error_) );
		}
		if( isRight ) {
			new (const_cast<A*>(static_cast<const A*>(&this->answer_))) A( (e.answer_) );
		}
	}
public:
	~Either() {
		if(isLeft) {
			this->error_.~E();
		}
		if(isRight) {
			this->answer_.~A();
		}

	}
	template <typename E_, typename A_> friend Either<E_,A_> Left(E_ const& x);
	template <typename E_, typename A_> friend Either<E_,A_> Right(A_ const& x);
public:
	typedef E error_type;
	typedef A answer_type;
public:
	std::string toString() const{
		return isRight ?
				cinamo::format("<Right[%s][%s]: %s>", cinamo::demangle<E>().c_str(), cinamo::demangle<A>().c_str(), cinamo::toString(answer_).c_str()) :
				cinamo::format("<Left[%s][%s]: %s>", cinamo::demangle<E>().c_str(), cinamo::demangle<A>().c_str(), cinamo::toString(error_).c_str());
	}
public:
	E error() const{
		return isLeft ? error_ : throw cinamo::format("Cannot get error from <Right[%s][%s]: %s>", cinamo::demangle<E>().c_str(), cinamo::demangle<A>().c_str(), cinamo::toString(answer_).c_str());
	}
	A answer() const{
		return isRight ? answer_ : throw cinamo::format("Cannot get answer from <Left[%s][%s]: %s>", cinamo::demangle<E>().c_str(), cinamo::demangle<A>().c_str(), cinamo::toString(error_).c_str());
	}
public:
	template <typename F>
	auto operator >>=(F f)
		-> Either<E, typename Ident<decltype(f(std::declval<A>()))>::type::answer_type> {
		return isLeft ?
			Left<E, typename  Ident<decltype(f(std::declval<A>()))>::type::answer_type>(error_) :
			f(answer_);
	}
	Either<E,A> operator ||(Either<E,A> const& e) {
		return isRight ? *this : e;
	}
	template <typename A2>
	auto operator >>(Either<E,A2> a) -> Either<E,A2> {
		return isRight ? a : Left<E,A2>(error_);
	}
	template <typename F>
	Either<E,A> fmap(F f){
		return isLeft ? *this : Right(f(answer_));
	}
	template <typename F> Either<E,A>& ifRight(F f) { if(isRight) f(answer_); return *this; }
	template <typename F> Either<E,A>& ifLeft(F f) { if(isLeft) f(error_); return *this; }

	template <typename F> Either<E,A> const& ifRight(F f) const { if(isRight) f(answer_); return *this; }
	template <typename F> Either<E,A> const& ifLeft(F f) const { if(isLeft) f(error_); return *this; }

	template <typename E_,typename A_,typename U_> friend class Either;
	template <typename E_,typename A_>
	constexpr bool operator ==(Either<E_,A_> const& o) const
	{
		return
			this->isRight ? ( std::is_same<A, A_>::value && o.isRight && answer_ == o.answer_ ) :
			this->isLeft ? (std::is_same<E, E_>::value && o.isLeft && error_ == o.error_) : false;
	}
	template <typename E_,typename A_>
	constexpr bool operator !=(Either<E_, A_> const& o) const
	{
		return !(this-> operator ==(o));
	}
};

}
