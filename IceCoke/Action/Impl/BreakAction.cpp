#include <string>
#include <vector>
#include <iostream>

#include "../Action.h"
#include "../ActionInitializer.h"

class BreakAction : public Action
{
public:
	void SetParameter(const ActionParameter &param);
	bool PerformAction(ActionContext &context);

private:
	std::vector<ActionParameter> actionParameters_;
};

IMPLEMENT_ACTION_INITIALIZER(Break);

void BreakAction::SetParameter(const ActionParameter &param)
{
	actionParameters_.push_back(param);
}

bool BreakAction::PerformAction(ActionContext &context)
{
	std::cout << std::endl;
	std::cout << "**** BREAK ****" << std::endl;

	std::cout << std::endl;
	std::cout << "Parameters" << std::endl;
	std::cout << "==========" << std::endl;
	std::cout << std::endl;

	if (actionParameters_.empty())
		std::cout << "(NO PARAMETER)" << std::endl;

	for (std::vector<ActionParameter>::iterator it = actionParameters_.begin(); it != actionParameters_.end(); ++it)
		std::cout << it->name << ": " << it->value << std::endl;

	std::cout << std::endl;
	std::cout << "Context" << std::endl;
	std::cout << "=======" << std::endl;
	std::cout << std::endl;

	if (context.empty())
		std::cout << "(NO CONTEXT)" << std::endl;

	for (ActionContext::iterator it = context.begin(); it != context.end(); ++it)
		std::cout << it->first << ": " << it->second << std::endl;

	std::cout << std::endl;
	std::cout << "**** BREAK ****" << std::endl;
	std::cout << std::endl;

	std::cout << "Press ENTER to continue..." << std::endl;
	std::string line;
	std::getline(std::cin, line);
	return true;
}
