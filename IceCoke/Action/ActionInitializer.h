#ifndef ACTION_INITIALIZER_H
#define ACTION_INITIALIZER_H

#include "Action.h"

typedef Action* (*ActionInitializer)();

#define NAME_INITIALIZER(NAME) \
	Init##NAME##Action

#define DECLARE_ACTION_INITIALIZER(NAME) \
	Action* NAME_INITIALIZER(NAME)()

#define IMPLEMENT_ACTION_INITIALIZER(NAME) \
	DECLARE_ACTION_INITIALIZER(NAME) \
	{ \
		return new NAME##Action(); \
	}

#endif
