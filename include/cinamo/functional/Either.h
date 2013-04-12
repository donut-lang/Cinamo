/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2013, psi
 */
#pragma once

#include "Maybe.h"

namespace cinamo {

template <typename R>
struct _remove_either {
	typedef typename R::error_type error_type;
	typedef typename R::answer_type answer_type;
};

template <typename E, typename A> class Either;
template <typename E, typename A> constexpr Either<E,A> Left(E const& e);
template <typename E, typename A> constexpr Either<E,A> Right(A const& a);

template <typename E, typename A>
class Either {
public:
	bool const isLeft;
	bool const isRight;
private:
	E const error_;
	A const answer_;
	constexpr Either(E const& e, std::true_type const&)
	:isLeft(true)
	,isRight(false)
	,error_(e)
	,answer_(){}
	constexpr Either(A const& a, std::false_type const&)
	:isLeft(false)
	,isRight(true)
	,error_()
	,answer_(a){}
	template <typename E_, typename A_> friend constexpr Either<E_,A_> Left(E_ const& x);
	template <typename E_, typename A_> friend constexpr Either<E_,A_> Right(A_ const& x);
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
	constexpr E error() const{
		return isLeft ? error : throw cinamo::format("Cannot get error from <Right[%s][%s]: %s>", cinamo::demangle<E>().c_str(), cinamo::demangle<A>().c_str(), cinamo::toString(answer_).c_str());
	}
	constexpr A answer() const{
		return isRight ? answer_ : throw cinamo::format("Cannot get answer from <Left[%s][%s]: %s>", cinamo::demangle<E>().c_str(), cinamo::demangle<A>().c_str(), cinamo::toString(error_).c_str());
	}
public:
	template <typename F>
	constexpr auto operator >>=(F f)
		-> Either<E, typename _remove_either<decltype(f(std::declval<A>()))>::answer_type> {
		return isLeft ?
			Left<E, typename _remove_either<decltype(f(std::declval<A>()))>::answer_type>(error_) :
			f(answer_);
	}
	constexpr Either<E,A> operator ||(Either<E,A> e) {
		return isRight ? *this : e;
	}
	template <typename A2>
	constexpr auto operator >>(Either<E,A2> a) -> Either<E,A2> {
		return Left<E,A2>(error);
	}
	template <typename F>
	constexpr Either<E,A> fmap(F f){
		return isLeft ? *this : Right(f(answer_));
	}
	template <typename F>
	constexpr auto ifRight(F f) -> Maybe<decltype(f(answer_))>{
		return isRight ? Just(f(answer_)) : Nothing<decltype(f(answer_))>();
	}
	template <typename F>
	constexpr auto ifLeft(F f) -> Maybe<decltype(f(error_))>{
		return isLeft ? Just(f(error_)) : Nothing<decltype(f(error_))>();
	}
	~Either() = default;
};

template <typename E, typename A>
constexpr Either<E,A> Left(E const& e) {
	return Either<E,A>(e, std::true_type());
}

template <typename E, typename A>
constexpr Either<E,A> Right(A const& a){
	return Either<E,A>(a, std::false_type());
}

}
