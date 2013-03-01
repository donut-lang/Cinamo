/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 */

#include <tarte/String.h>
#include <tarte/Exception.h>

namespace tarte {

Exception::Exception(const char* file, const size_t line) throw()
{
	init(file, line, "");
}

Exception::Exception(const char* file, const size_t line, std::string const& fmt, ...) noexcept
{
	va_list lst;
	va_start(lst, fmt);
	init(file, line, fmt, lst);
	va_end(lst);
}

Exception::Exception(const char* file, const size_t line, std::string const& fmt, va_list lst) noexcept
{
	init(file, line, fmt, lst);
}

void Exception::init(const char* file, const size_t line, std::string const& fmt, ...) noexcept
{
	va_list lst;
	va_start(lst, fmt);
	init(file, line, fmt, lst);
	va_end(lst);
}

void Exception::init(const char* file, const size_t line, std::string const& fmt, va_list lst) noexcept
{
	try{
		this->_line = line;
		this->_file = std::string(file);
		this->_loc = format("(in %s:%d): ", file, line);
		this->_msg = formatv(fmt, lst);
		this->_what = _loc+_msg;
	}catch(...){
		this->_line = 0;
		this->_file = __FILE__;
		this->_loc = "line ? in " __FILE__ ": ";
		this->_msg = "[BUG] Failed to format string!!";
		this->_what = _loc+_msg;
	}
}

const char* Exception::what() const noexcept (true)
{
	return _what.c_str();
}

std::string Exception::msg() const noexcept
{
	return _msg;
}
size_t Exception::line() const noexcept
{
	return _line;
}

std::string Exception::file() const noexcept
{
	return _file;
}

}
