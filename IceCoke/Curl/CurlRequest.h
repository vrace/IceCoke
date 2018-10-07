#ifndef CURL_REQUEST_H
#define CURL_REQUEST_H

#include <stdio.h>
#include <stdlib.h>

#include <string>

class CurlRequest
{
public:
	CurlRequest();
	~CurlRequest();

	void CloseRequest();

	bool SetHeader(const std::string &name, const std::string &value);
	bool SetBody(const std::string &body);

	bool HasHeaders() const;
	bool HasBody() const;

	const std::string& HeadersFileName();
	const std::string& BodyFileName();

private:
	CurlRequest(const CurlRequest&);
	CurlRequest& operator=(const CurlRequest&);

	FILE* HeadersFile();
	FILE* BodyFile();

private:
	FILE *headers_;
	FILE *body_;
	bool hasHeaders_;
	bool hasBody_;
};

#endif
