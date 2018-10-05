#include "ActionFactory.h"

ActionFactory::ActionFactory()
{

}

ActionFactory::~ActionFactory()
{

}

Action* ActionFactory::CreateAction(const std::string &name)
{
	ActionInitializerList::iterator it = actionInitializers_.find(name);
	
	if (it == actionInitializers_.end())
		return NULL;

	ActionInitializer initializer = it->second;
	return initializer();
}

void ActionFactory::SetInitializer(const std::string &name, ActionInitializer initializer)
{
	actionInitializers_[name] = initializer;
}
