#ifndef CURL_RESPONSE_H
#define CURL_RESPONSE_H

#include <string>
#include <map>

typedef std::map<std::string, std::string> CurlResponseHeaders;

struct CurlResponse
{
	CurlResponse();
	CurlResponse(int statusCode, const CurlResponseHeaders &headers, const std::string &body);

	int statusCode;
	CurlResponseHeaders headers;
	std::string body;
};

#endif
