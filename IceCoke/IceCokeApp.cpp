#include <iostream>
#include <fstream>
#include <memory>

#include "IceCokeApp.h"
#include "Setup/ActionFactorySetup.h"
#include "Scripting/ScriptCompiler.h"
#include "IceCokeScriptCompilerDelegate.h"

#include "Curl/CurlExec.h"

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
	std::auto_ptr<Script> script(compiler.Compile());

	if (!script.get())
		return EXIT_FAILURE;

	return script->Run() ? 0 : EXIT_FAILURE;
}
