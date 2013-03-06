/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#pragma once

#include <ostream>
#include <cstdarg>
#include <string>
#include "Common.h"

namespace cinamo {

/**
 * ロガー。
 *
 * ログを書き出す先を抽象化して、
 * ログレベル管理やプリティプリントなどの
 * ユーティリティを付加したクラス。
 */
class Logger {
public:
	enum Level{
		TRACE_=0,
		VERBOSE_=1,
		DEBUG_=2,
		INFO_=3,
		WARN_=4,
		ERROR_=5,
	};
private:
	std::ostream& _stream;
	enum Level level;
	void msg(enum Level level, std::string const& tag, std::string const& fmt, std::va_list args);
public:
	Logger(std::ostream& stream, enum Level level) noexcept;
	~Logger() noexcept = default;
public:
	std::ostream& stream() const noexcept{ return _stream; };
public:
	bool t() const noexcept;
	void t(std::string const& tag, std::string const& fmt, ...);
	bool v() const noexcept;
	void v(std::string const& tag, std::string const& fmt, ...);
	bool d() const noexcept;
	void d(std::string const& tag, std::string const& fmt, ...);
	bool i() const noexcept;
	void i(std::string const& tag, std::string const& fmt, ...);
	void w(std::string const& tag, std::string const& fmt, ...);
	void e(std::string const& tag, std::string const& fmt, ...);
};

}

