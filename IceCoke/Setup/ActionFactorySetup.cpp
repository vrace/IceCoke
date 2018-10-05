#include "ActionFactorySetup.h"
#include "../Action/ActionFactory.h"
#include "../Action/ActionInitializer.h"

#define SET_INITIALIZER(NAME) \
	DECLARE_ACTION_INITIALIZER(NAME); \
	factory->SetInitializer(#NAME, NAME_INITIALIZER(NAME));

void ActionFactorySetup::Setup()
{
	ActionFactory *factory = ActionFactory::GetInstance();

	SET_INITIALIZER(Break);
}
