#include "CurlResponse.h"

CurlResponse::CurlResponse()
	: statusCode(0)
{

}

CurlResponse::CurlResponse(int theCode, const CurlResponseHeaders &theHeaders, const std::string &theBody)
	: statusCode(theCode)
	, headers(theHeaders)
	, body(theBody)
{

}
