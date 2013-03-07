/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cinamo/Logger.h>
#include <cinamo/Exception.h>
#include <cinamo/String.h>

namespace cinamo {

Logger::Logger(std::ostream& stream, enum Level level) noexcept
:_stream(stream), level(level)
{
}

void Logger::msg(enum Level level, std::string const& tag, std::string const& fmt, std::va_list args)
{
	std::stringstream ss;
	if(level < this->level){
		return;
	}
	switch(level){
	case TRACE_:
		ss << "[T]";
		break;
	case VERBOSE_:
		ss << "[V]";
		break;
	case DEBUG_:
		ss << "[D]";
		break;
	case INFO_:
		ss << "[I]";
		break;
	case WARN_:
		ss << "[W]";
		break;
	case ERROR_:
		ss << "[E]";
		break;
	default:
		throw Exception(__FILE__, __LINE__, "[BUG][FIXME] Invalid log level!!");
	}
	ss << "[" << std::setw(16) << tag << "] ";
	ss << formatv(fmt, args) << std::endl;
	_stream << ss.str();
	_stream.flags();
}

void Logger::t(std::string const& tag, std::string const& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(TRACE_, tag, fmt, lst);
	va_end(lst);

}

void Logger::v(std::string const& tag, std::string const& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(VERBOSE_, tag, fmt, lst);
	va_end(lst);
}

void Logger::d(std::string const& tag, std::string const& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(DEBUG_, tag, fmt, lst);
	va_end(lst);
}

void Logger::i(std::string const& tag, std::string const& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(INFO_, tag, fmt, lst);
	va_end(lst);
}
void Logger::w(std::string const& tag, std::string const& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(WARN_, tag, fmt, lst);
	va_end(lst);
}
void Logger::e(std::string const& tag, std::string const& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(ERROR_, tag, fmt, lst);
	va_end(lst);
}

}
