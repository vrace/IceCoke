#include "Script.h"

Script::Script()
{

}

Script::~Script()
{
	for (ActionList::iterator it = actionList_.begin(); it != actionList_.end(); ++it)
	{
		Action *action = *it;
		delete action;
	}
	actionList_.clear();
}

void Script::AppendAction(Action *action)
{
	actionList_.push_back(action);
}

bool Script::Run()
{
	ActionContext context;
	return Run(context);
}

bool Script::Run(ActionContext &context)
{
	for (ActionList::iterator it = actionList_.begin(); it != actionList_.end(); ++it)
	{
		Action *action = *it;
		if (!action->PerformAction(context))
			return false;
	}

	return true;
}
