#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>
#include "../Action/Action.h"
#include "../Action/ActionContext.h"

class Script
{
public:
	typedef std::vector<Action*> ActionList;

	Script();
	~Script();

	void AppendAction(Action *action);

	bool Run();
	bool Run(ActionContext &context);

private:
	Script(const Script&);
	Script& operator=(const Script&);

private:
	ActionList actionList_;
};

#endif
