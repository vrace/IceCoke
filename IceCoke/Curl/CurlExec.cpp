#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "CurlExec.h"

namespace
{
	const char RESPONSE_HEADERS[] = "response_headers.txt";
	const char RESPONSE_BODY[] = "response_body.txt";
	const char CURL_EXEC[] = "curl_exec.bat";
}

CurlExec::CurlExec()
	: response_(NULL)
{

}

CurlExec::~CurlExec()
{
	if (response_)
		delete response_;
}

CurlRequest* CurlExec::Request()
{
	return &request_;
}

CurlResponse* CurlExec::PerformCurl(const std::string &method, const std::string &url)
{
	if (response_ || method.empty() || url.empty())
		return NULL;

	if (!PrepareExec(method, url))
		return NULL;

	request_.CloseRequest();

	if (system(CURL_EXEC) == 0)
		LoadResponse();

	return response_;
}

bool CurlExec::PrepareExec(const std::string &method, const std::string &url)
{
	std::ofstream fs(CURL_EXEC, std::ios::trunc | std::ios::out);

	fs << "@echo off" << std::endl;
	fs << "curl -s -k -X " << method << " ";
	if (request_.HasHeaders())
		fs << "-H @" << request_.HeadersFileName() << " ";
	fs << "-D " << RESPONSE_HEADERS << " ";
	if (request_.HasBody())
		fs << "--data-binary @" << request_.BodyFileName() << " ";
	fs << url << " > " << RESPONSE_BODY << std::endl;

	return !!fs;
}

void CurlExec::LoadResponse()
{
	response_ = new CurlResponse();
	LoadResponseHeaders();
	LoadResponseBody();
}

void CurlExec::LoadResponseHeaders()
{
	std::ifstream fs(RESPONSE_HEADERS);

	if (!fs)
		return;

	std::string line;
	if (!std::getline(fs, line))
		return;

	LoadResponseStatusCode(line);

	while (getline(fs, line))
	{
		std::string::size_type delim = line.find(':');
		if (delim != std::string::npos)
		{
			std::string name = line.substr(0, delim);
			std::string value;
			std::string::size_type valueStart = line.find_first_not_of(' ', delim + 1);
			if (valueStart != std::string::npos)
				value = line.substr(valueStart);

			response_->headers[name] = value;
		}
	}
}

void CurlExec::LoadResponseStatusCode(const std::string &line)
{
	if (line.find("HTTP") != 0)
		return;

	std::stringstream ss(line);
	std::string version;
	ss >> version >> response_->statusCode;
}

void CurlExec::LoadResponseBody()
{
	std::ifstream fs(RESPONSE_BODY);

	if (!fs)
		return;

	response_->body.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
}
