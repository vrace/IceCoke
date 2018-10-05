#ifndef ACTION_PARAMETER_H
#define ACTION_PARAMETER_H

#include <string>

struct ActionParameter
{
	ActionParameter();
	ActionParameter(const std::string &name, const std::string &value);

	std::string name;
	std::string value;
};

#endif
