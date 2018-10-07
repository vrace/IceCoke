#ifndef CURL_EXEC_H
#define CURL_EXEC_H

#include <string>

#include "CurlRequest.h"
#include "CurlResponse.h"

class CurlExec
{
public:
	CurlExec();
	~CurlExec();

	CurlRequest* Request();
	CurlResponse* PerformCurl(const std::string &method, const std::string &url);

private:
	CurlExec(const CurlExec&);
	CurlExec& operator=(const CurlExec&);

	bool PrepareExec(const std::string &method, const std::string &url);
	void LoadResponse();
	void LoadResponseHeaders();
	void LoadResponseBody();
	void LoadResponseStatusCode(const std::string &header);

private:
	CurlRequest request_;
	CurlResponse *response_;
};

#endif
