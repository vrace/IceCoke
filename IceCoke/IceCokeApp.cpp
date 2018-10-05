#include <iostream>
#include <fstream>

#include "IceCokeApp.h"
#include "Setup/ActionFactorySetup.h"
#include "Scripting/ScriptCompiler.h"
#include "IceCokeScriptCompilerDelegate.h"

int IceCokeApp::Run(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: IceCoke <script file>" << std::endl;
		return EXIT_FAILURE;
	}

	std::ifstream fs(argv[1]);
	if (!fs)
	{
		std::cout << "ERROR: Script file '" << argv[1] << "' can't be opened." << std::endl;
		return EXIT_FAILURE;
	}

	ActionFactorySetup::Setup();

	IceCokeScriptCompilerDelegate delegate(fs);
	ScriptCompiler compiler(&delegate);
	Script *script = compiler.Compile();

	if (script)
	{
		script->Run();
		delete script;
	}

	return 0;
}
