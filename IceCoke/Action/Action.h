#ifndef ACTION_H
#define ACTION_H

#include <string>
#include "ActionParameter.h"
#include "ActionContext.h"

class Action
{
public:
	virtual ~Action() {};
	virtual void SetParameter(const ActionParameter &param) = 0;
	virtual bool PerformAction(ActionContext &context) = 0;
};

#endif
