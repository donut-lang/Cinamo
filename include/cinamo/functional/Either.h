/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2013, psi
 */
#pragma once

#include <utility>
#include <type_traits>
#include "Ident.h"
#include "Maybe.h"

namespace cinamo {

template <typename E, typename A> class Either;
template <typename E, typename A>
constexpr Either<E,A> Left(E const& e) {
	return Either<E,A>(e, std::true_type());
}

template <typename E, typename A>
constexpr Either<E,A> Right(A const& a){
	return Either<E,A>(a, std::false_type());
}

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
		-> Either<E, typename Ident<decltype(f(std::declval<A>()))>::type::answer_type> {
		return isLeft ?
			Left<E, typename  Ident<decltype(f(std::declval<A>()))>::type::answer_type>(error_) :
			f(answer_);
	}
	constexpr Either<E,A> operator ||(Either<E,A> const& e) {
		return isRight ? *this : e;
	}
	template <typename A2>
	constexpr auto operator >>(Either<E,A2> a) -> Either<E,A2> {
		return isRight ? a : Left<E,A2>(error_);
	}
	template <typename F>
	constexpr Either<E,A> fmap(F f){
		return isLeft ? *this : Right(f(answer_));
	}
	template <typename F>
	constexpr auto ifRight(F f, typename std::enable_if<std::is_same<typename Ident<decltype(f(answer_))>::type, void>::value>::type* = 0) -> void{
		if(isRight) {
			f(answer_);
		}
	}
	template <typename F>
	constexpr auto ifLeft(F f, typename std::enable_if<std::is_same<typename Ident<decltype(f(error_))>::type, void>::value>::type* = 0) -> void{
		if(isLeft) {
			f(error_);
		}
	}
	template <typename F>
	constexpr auto ifRight(F f, typename std::enable_if<!std::is_same<typename Ident<decltype(f(answer_))>::type, void>::value>::type* = 0) -> Maybe<decltype(f(answer_))>{
		return isRight ? Just(f(answer_)) : Nothing<decltype(f(answer_))>();
	}
	template <typename F>
	constexpr auto ifLeft(F f, typename std::enable_if<!std::is_same<typename Ident<decltype(f(error_))>::type, void>::value>::type* = 0) -> Maybe<decltype(f(error_))>{
		return isLeft ? Just(f(error_)) : Nothing<decltype(f(error_))>();
	}
	template <typename E_,typename A_> friend class Either;
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
	~Either() = default;
};

}
