#ifndef ACTION_FACTORY_H
#define ACTION_FACTORY_H

#include <map>
#include "Action.h"
#include "ActionInitializer.h"
#include "../Utility/Singleton.h"

class ActionFactory : public Singleton<ActionFactory>
{
public:
	friend class Singleton<ActionFactory>;
	typedef std::map<std::string, ActionInitializer> ActionInitializerList;

	Action* CreateAction(const std::string &name);
	void SetInitializer(const std::string &name, ActionInitializer initializer);

private:
	ActionFactory();
	~ActionFactory();
	ActionFactory(const ActionFactory&);
	ActionFactory& operator=(const ActionFactory&);

private:
	ActionInitializerList actionInitializers_;
};

#endif
