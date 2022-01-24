#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <set>
using namespace std;

class Stats {
public:
	Stats() {
		_createMethodMap();
		_createUriMap();
	}
	//+Method UNKNOWN
  void AddMethod(string_view method);
  //+uri "unknown"
  void AddUri(string_view uri);


  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
	map<string_view, int> _method_stats;
	map<string_view, int> _uri_stats;
	void _createMethodMap();
	void _createUriMap();
	const set<string_view> _methods = { "GET", "POST", "PUT", "DELETE" };
	const set<string_view> _uris = { "/", "/order", "/product", "/basket", "/help" };
};


HttpRequest ParseRequest(string_view line);
