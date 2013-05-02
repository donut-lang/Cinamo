/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */
#pragma once
#include <cstddef>
#include <type_traits>
#include <cassert>
#include <array>

namespace cinamo {

template <size_t N, size_t M=N>
class Mat final{
private:
	std::array<double, N*M> val_;
private:
	Mat(std::array<double, N*M>&& val):val_(val){};
public:
	Mat():val_(){};
	Mat(Mat<N,M> const& o):val_(o.val_){};
	Mat(Mat<N,M>&& o):val_(std::move(o.val_)){};

	Mat<N,M>& operator=(Mat<N,M> const& o){
		val_ = o.val_;
		return *this;
	};
	Mat<N,M>& operator=(Mat<N,M>&& o){
		val_ = std::move(o.val_);
		return *this;
	}
public:
	template<typename ...E>
	constexpr Mat(E&& ...e)
	:val_{{std::forward<E>(e)...}}{
		static_assert((sizeof...(E)) == N*M, "size not match");
	}
	~Mat() = default;
public:
	double const& operator()(size_t i, size_t j) const{
		assert(i >= 0 && i< N);
		assert(j >= 0 && j< M);
		return val_[i*M+j];
	}
	double& operator()(size_t i, size_t j){
		assert(i >= 0 && i< N);
		assert(j >= 0 && j< M);
		return val_[i*M+j];
	}
	Mat<N,M>& operator *=(double const& o) {
		for(double &d : val_){
			d *= o;
		}
		return *this;
	}
	Mat<N,M> operator *(double const& o) const{
		Mat<N,M> self(*this);
		self *= o;
		return self;
	}
	// 同じ次元の正方行列
	template <size_t N_, size_t M_>
	auto operator *=(Mat<N_,M_> const& o)
	-> typename std::enable_if<N_==N&&M_==M&&N==M, Mat<N,M>& >::type
	{
		for(size_t i=0;i<N;++i) {
			for(size_t j=0;j<N;++j) {
				double sum = 0;
				for(size_t k=0;k<N;++k){
					sum += ((*this)(i, k))*(o(k,j));
				}
				(*this)(i,j)=sum;
			}
		}
		return *this;
	}
	// 同じ次元の正方行列
	template <size_t N_, size_t M_>
	auto operator *(Mat<N_,M_> const& o) const
	-> typename std::enable_if<N_==N&&M_==M&&N==M, Mat<N,M> >::type
	{
		Mat <N,M> self(*this);
		self*=o;
		return std::move(self);
	}
	// そうでない
	template <size_t L>
	auto operator *(Mat<M, L> const& o) const
	-> typename std::enable_if<N!=M || L!=M, Mat<N,L> >::type
	{
		Mat<N,L> val;
		for(size_t i=0;i<N;++i) {
			for(size_t j=0;j<L;++j) {
				double sum = 0;
				for(size_t k=0;k<M;++k){
					sum += ((*this)(i, k))*o(k,j);
				}
				val(i,j)=sum;
			}
		}
		return val;
	}
	Mat<N,M>& operator +=(Mat<N,M> const& o)
	{
		for(size_t i=0;i<N;++i) {
			for(size_t j=0;j<M;++j) {
				(*this)(i,j)+=o(i,j);
			}
		}
		return *this;
	}

	Mat<N,M> operator +(Mat<N,M> const& o) const{
		Mat<N, M> self(*this);
		return std::move(self += o);
	}
};

}
