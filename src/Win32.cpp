/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#include <tarte/Platform.h>
#if TARTE_WINDOWS
#include <tarte/internal/Win32.h>
#include <tarte/Logger.h>
#include <tarte/Exception.h>

namespace tarte {
namespace internal {
namespace win32 {

std::wstring toUTF16(std::string const& str)
{
	int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), nullptr, 0);
	wchar_t* buf = new wchar_t[size+1];
	if(size != MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), buf, size+1)){
		TARTE_EXCEPTION(Exception, "Failed to convert UTF8 to UTF16");
	}
	buf[size]=0;
	std::wstring ret(buf);
	delete [] buf;
	return ret;
}
std::string toUTF8(std::wstring const& str)
{
	int size = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), nullptr, 0, nullptr, nullptr);
	char* buf = new char[size+1];
	if(size != WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), buf, size+1, nullptr, nullptr)){
		TARTE_EXCEPTION(Exception, "Failed to convert UTF8 to UTF16");
	}
	buf[size]=0;
	std::string ret(buf);
	delete [] buf;
	return ret;
}

}}}

#endif
