/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 */

#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>
#include <sstream>

#include <unicode/unistr.h>
#include <unicode/regex.h>
#include <unicode/brkiter.h>

#include <tarte/Exception.h>
#include <tarte/Platform.h>
#include <tarte/String.h>

#if TARTE_WINDOWS
#define _LONG_LONG_INT_FORMAT_ "I64"
#else
#define _LONG_LONG_INT_FORMAT_ "ll"
#endif

namespace tarte {

std::string format(std::string const& fmt, ...)
{
	va_list lst;
	va_start(lst, fmt);
	std::string res(formatv(fmt, lst));
	va_end(lst);
	return res;
}
std::string formatv(std::string const& fmt, va_list args)
{
	char buff[8192];
	size_t len = vsnprintf(buff, 8192, fmt.c_str(), args);
	if(len < 0){
		TARTE_EXCEPTION(Exception, "Format string too long!!");
	}
	return buff;
}

#define TOSTR_DEF(type, fmtstr8, fmtstr10, fmtstr16)\
std::string toString(type const& val, int radix) {\
	switch(radix){\
	case 0:\
		return format(fmtstr10, val);\
	case 8:\
		return format(fmtstr8, val);\
	case 10:\
		return format(fmtstr10, val);\
	case 16:\
		return format(fmtstr16, val);\
	default:\
		TARTE_EXCEPTION(Exception, "[BUG] Unknwon radix: %d", radix);\
		return "dummy for ignore warning.";\
	}\
}

#if ((CHAR_MIN) == 0) //CHARが符号付きかどうかは環境依存です。
TOSTR_DEF(char, "0%o", "%u", "0x%x");
#else
TOSTR_DEF(char, "0%o", "%d", "0x%x");
#endif
TOSTR_DEF(unsigned char, "0%o", "%u", "0x%x");
TOSTR_DEF(signed char, "0%o", "%d", "0x%x");

TOSTR_DEF(int, "0%o", "%d", "0x%x");
TOSTR_DEF(unsigned int, "0%o", "%u", "0x%x");
// メモリモデルによってlong intの値は違う
#if INT_MAX == LONG_MAX
TOSTR_DEF(long int, "0%o", "%d", "0x%x");
TOSTR_DEF(unsigned long int, "0%o", "%u", "0x%x");
#elif LONG_MAX > INT_MAX
TOSTR_DEF(long int, "0%" _LONG_LONG_INT_FORMAT_ "o", "%" _LONG_LONG_INT_FORMAT_ "d", "0x%" _LONG_LONG_INT_FORMAT_ "x");
TOSTR_DEF(unsigned long int, "0%" _LONG_LONG_INT_FORMAT_ "o", "%" _LONG_LONG_INT_FORMAT_ "u", "0x%" _LONG_LONG_INT_FORMAT_ "x");
#else
#error "Unknwon data type."
#endif

TOSTR_DEF(long long int, "0%" _LONG_LONG_INT_FORMAT_ "o", "%" _LONG_LONG_INT_FORMAT_ "d", "0x%" _LONG_LONG_INT_FORMAT_ "x");
TOSTR_DEF(unsigned long long int, "0%" _LONG_LONG_INT_FORMAT_ "o", "%" _LONG_LONG_INT_FORMAT_ "u", "0x%" _LONG_LONG_INT_FORMAT_ "x");

#undef TOSTR_DEF

std::string toString(const float val)
{
	if(!(val == val)){
		return "nan";
	}else if(!std::isfinite(val)){
		return val < 0 ? "-infinity" : "infinity";
	}
	return format("%f", val);
}

std::string toString(const double val)
{
	if(!(val == val)){
		return "nan";
	}else if(!std::isfinite(val)){
		return val < 0 ? "-infinity" : "infinity";
	}
	return format("%f", val);
}

std::string toString(const bool val)
{
	return val ? "true" : "false";
}

std::string join(std::vector<std::string> const& lst)
{
	std::stringstream ss;
	for(std::string const& str : lst) {
		ss << str;
	}
	return ss.str();
}

std::string join(std::vector<std::string> const& lst, std::string const& sep)
{
	std::stringstream ss;
	bool isNotFirst = false;
	for(std::string const& str : lst) {
		if(isNotFirst){
			ss << sep;
		}
		ss << str;
		isNotFirst = true;
	}
	return ss.str();
}

std::vector<std::string> breakChar(std::string const& str_)
{
	UErrorCode st = U_ZERO_ERROR;
	BreakIterator* bi = BreakIterator::createCharacterInstance(Locale::getJapanese(), st);
	std::vector<std::string> list;
	UnicodeString str(UnicodeString::fromUTF8(str_));
	bi->setText(str);
	int32_t last = 0;
	int32_t p = bi->first();
	while (p != BreakIterator::DONE) {
		if(p == last){
			p = bi->next();
			continue;
		}
		std::string s;
		str.tempSubStringBetween(last, p).toUTF8String(s);
		list.push_back(s);
		last = p;
		p = bi->next();
	}
	delete bi;
	return list;
}

std::size_t matchString(std::string const& a, std::string const& b)
{
	std::size_t t = 0;
	for(std::string::value_type const& c : a){
		if(c != b[t]) {
			break;
		}
		++t;
	}
	return t;
}

#define PARSE_STRTO(TYPE, FUNC) \
template <>\
TYPE parseAs<TYPE>(std::string const& str, int radix, bool* succeed) {\
	char* end;\
	TYPE const result = std::FUNC(str.c_str(), &end, radix);\
	if((*end) != '\0'){\
		if(succeed != nullptr){\
			*succeed = false;\
		}else{\
			TARTE_EXCEPTION(Exception, "Invalid number: %s", str.c_str());\
		}\
	} else {\
		if(succeed) *succeed = true;\
	}\
	return result;\
}\
template <>\
TYPE parseAs<TYPE>(std::string const& str, bool* succeed) {\
	return parseAs<TYPE>(str, 0, succeed);\
}

PARSE_STRTO(char, strtol);
PARSE_STRTO(signed char, strtol);
PARSE_STRTO(unsigned char, strtoul);

PARSE_STRTO(short, strtol);
PARSE_STRTO(unsigned short, strtoul);

PARSE_STRTO(int, strtol);
PARSE_STRTO(unsigned int, strtoul);

PARSE_STRTO(long int, strtol);
PARSE_STRTO(long unsigned int, strtoul);

#if HAVE_LONG_LONG
PARSE_STRTO(long long int, strtoll);
PARSE_STRTO(unsigned long long int, strtoull);
#endif

#define PARSE_STRTO_F(TYPE, FUNC) \
	template <> TYPE parseAs<TYPE>(std::string const& str, bool* succeed)\
	{\
		char* end;\
		TYPE const result = FUNC(str.c_str(), &end);\
		if((*end) != '\0'){\
			if(succeed != nullptr){\
				*succeed = false;\
			}else{\
				TARTE_EXCEPTION(Exception, "Invalid number: %s", str.c_str());\
			}\
		} else {\
			if(succeed) *succeed = true;\
		}\
		return result;\
	}


PARSE_STRTO_F(float, strtof);
PARSE_STRTO_F(double, strtod);
#if HAVE_LONG_DOUBLE
PARSE_STRTO_F(long double, strtold);
#endif

#undef PARSE_STRTO_F
#undef PARSE_STRTO

template <>
bool parseAs<bool>(std::string const& str, bool* succeed)
{
	std::string copy = toLower(str);
	if( copy == "true" || copy == "yes") {
		if(succeed) *succeed = true;
		return true;
	} else if(copy == "false" || copy=="no") {
		if(succeed) *succeed = true;
		return false;
	} else if(succeed){
		*succeed = false;
	} else {
		TARTE_EXCEPTION(Exception, "Invalid boolean: %s", str.c_str());
	}
	return false;
}

const static char RandChar[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',};

std::string randomString(std::size_t len)
{
	std::stringstream ss;
	for(std::size_t i = 0;i<len;++i){
		ss << RandChar[ std::rand() % (sizeof(RandChar)/sizeof(char)) ];
	}
	return ss.str();
}

std::string decodePercent(std::string const& str)
{
	char* from(new char[str.length()+1]);
	char* to(new char[str.length()+1]);
	std::memcpy(from, str.c_str(), str.length());
	from[str.length()] = '\0';
	size_t i=0,j=0;
	for(;i<str.length();++i, ++j){
		if(from[i] == '%'){
			char code[3];
			code[0] = from[i+1];
			code[1] = from[i+2];
			code[2] = '\0';
			i+=2;
			char* failed = 0;
			to[j] = static_cast<char>(std::strtol(code, &failed, 16) & 0xff);
			if(failed != &code[2]){
				TARTE_EXCEPTION(Exception, "Failed to decode percent: %s", str.c_str());
			}
		}else if(from[i]=='+'){
			to[j] = ' ';
		}else{
			to[j] = from[i];
		}
	}
	to[j]='\0';

	std::string res(to);

	delete [] from;
	delete [] to;

	return res;
}

std::string toLower(std::string const& str)
{
	std::string copy(str);
	std::transform(copy.begin(), copy.end(), copy.begin(), (int (*)(int))std::tolower);
	return copy;
}

std::string toUpper(std::string const& str)
{
	std::string copy(str);
	std::transform(copy.begin(), copy.end(), copy.begin(), (int (*)(int))std::toupper);
	return copy;
}

bool startsWith(std::string const& target, std::string const& prefix)
{
	return target.compare(0, prefix.size(), prefix) == 0;
}
bool endsWith(std::string const& target, std::string const& suffix)
{
	return target.compare(target.size()-suffix.size(), suffix.size(), suffix) == 0;
}

void split(std::string const& str, std::string const& sep, std::vector<std::string>& list)
{
	if(sep.size() <= 0){
		return;
	}
	size_t i = 0;
	size_t found = 0;
	while((found = str.find(sep, i)) != std::string::npos){
		if(found != i){
			list.push_back(str.substr(i, found-i));
		}
		i = found+sep.length();
	}
	if(i != str.size()){
		list.push_back(str.substr(i));
	}
}

static size_t findFirstOf(std::string const& str, const std::string* sep, size_t n, size_t from, size_t* offset, size_t* seplen)
{
	*offset = std::string::npos;
	for(size_t i = 0;i<n;++i){
		size_t found = str.find(sep[i], from);
		if(sep[i].size() > 0 && found != std::string::npos && (found < *offset || *offset == std::string::npos)){
			*offset = found;
			*seplen = sep[i].size();
		}
	}
	return *offset;
}

void split(std::string const& str, const std::string* sep, size_t n, std::vector<std::string>& list)
{
	size_t i = 0;
	size_t found = std::string::npos;
	size_t seplen = std::string::npos;
	while((findFirstOf(str, sep, n, i, &found, &seplen)) != std::string::npos){
		if(found != i){
			list.push_back(str.substr(i, found-i));
		}
		i = found+seplen;
	}
	if(i != str.size()){
		list.push_back(str.substr(i));
	}
}
void splitLine(std::string const& str, std::vector<std::string>& list)
{
	static const std::string lineSep[] = {
			"\n",
			"\r"
	};
	split(str, lineSep, list);
}
void splitSpace(std::string const& str, std::vector<std::string>& list)
{
	static const std::string spaces[] = {
			" ",
			"　"
	};
	split(str, spaces, list);
}

}
