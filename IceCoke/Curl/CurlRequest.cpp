#include "CurlRequest.h"

namespace
{
	const std::string REQUEST_HEADERS = "request_headers.txt";
	const std::string REQUEST_BODY = "request_body.txt";
}

CurlRequest::CurlRequest()
	: headers_(NULL)
	, body_(NULL)
	, hasHeaders_(false)
	, hasBody_(false)
{

}

CurlRequest::~CurlRequest()
{
	CloseRequest();
}

void CurlRequest::CloseRequest()
{
	if (headers_)
		fclose(headers_);

	if (body_)
		fclose(body_);

	headers_ = NULL;
	body_ = NULL;
}

bool CurlRequest::SetHeader(const std::string &name, const std::string &value)
{
	if (name.empty())
		return false;

	FILE *fp = HeadersFile();

	if (fp)
	{
		int sizeWrite = fprintf(fp, "%s: %s\n", name.c_str(), value.c_str());

		if (sizeWrite > 0)
			hasHeaders_ = true;

		return sizeWrite > 0;
	}

	return false;
}

bool CurlRequest::SetBody(const std::string &body)
{
	if (body.empty())
		return false;

	FILE *fp = BodyFile();

	if (fp)
	{
		int sizeWrite = fprintf(fp, "%s\n", body.c_str());

		if (sizeWrite > 0)
			hasBody_ = true;

		return sizeWrite > 0;
	}

	return false;
}

bool CurlRequest::HasHeaders() const
{
	return hasHeaders_;
}

bool CurlRequest::HasBody() const
{
	return hasBody_;
}

const std::string& CurlRequest::HeadersFileName()
{
	return REQUEST_HEADERS;
}

const std::string& CurlRequest::BodyFileName()
{
	return REQUEST_BODY;
}

FILE* CurlRequest::HeadersFile()
{
	if (!headers_)
		headers_ = fopen(HeadersFileName().c_str(), "w");

	return headers_;
}

FILE* CurlRequest::BodyFile()
{
	if (!body_)
		body_ = fopen(BodyFileName().c_str(), "w");

	return body_;
}
