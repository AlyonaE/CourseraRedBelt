#include "stats.h"

void Stats::AddMethod(string_view method)
{
	if (_methods.find(method) != _methods.end()) {
		_method_stats[method]++;
	}
	else {
		_method_stats["UNKNOWN"]++;
	}
}

void Stats::AddUri(string_view uri)
{
	if (_uris.find(uri) != _uris.end()) {
		_uri_stats[uri]++;
	}
	else {
		_uri_stats["unknown"]++;
	}
}

const map<string_view, int>& Stats::GetMethodStats() const
{
	return _method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const
{
	return _uri_stats;
}

void Stats::_createMethodMap()
{
	for (auto& item : _methods) {
		_method_stats[item] = 0;
	}
	_method_stats["UNKNOWN"] = 0;
}

void Stats::_createUriMap()
{
	for (auto& item : _uris) {
		_uri_stats[item] = 0;
	}
	_uri_stats["unknown"] = 0;
}

HttpRequest ParseRequest(string_view line)
{
	HttpRequest res;
	size_t pos = 0;
	while (line[pos] == ' ') {
		pos++;
	}
	size_t space = line.find(' ', pos);
	res.method = line.substr(pos, space - pos);
	pos = space + 1;
	space = line.find(' ', pos);
	res.uri = line.substr(pos, space - pos);
	pos = space + 1;
	res.protocol = line.substr(pos);
	return res;
}
