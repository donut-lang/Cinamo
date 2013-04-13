/* coding: utf-8 */
/**
 * Cinamo
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <string>
#include <map>
#include <vector>
#include <cinamo/ClassUtil.h>

namespace cinamo {

class FormPayload final {
private:
	std::map<std::string, std::string> map;
public:
	FormPayload();
	~FormPayload() = default;
public:
	DEFAULT_COPY_AND_ASSIGN(FormPayload);
public:
	void readURLEncoded(const std::string& data);
	typedef std::map<std::string, std::string>::const_iterator Iterator;
	size_t size() const;
	bool has(const std::string& key) const;
	std::string getString(const std::string& key) const;
	std::string optString(const std::string& key, const std::string& def) const;
	long long getLong(const std::string& key) const;
	long long optLong(const std::string& key, long long def) const;
	bool getBool(const std::string& key) const;
	bool optBool(const std::string& key, bool def) const;
	Iterator begin() const;
	Iterator end() const;
};

}
