#include "IceCokeScriptCompilerDelegate.h"

IceCokeScriptCompilerDelegate::IceCokeScriptCompilerDelegate(std::istream &input)
	: input_(input)
{

}

bool IceCokeScriptCompilerDelegate::NextLine(std::string &line)
{
	return !!std::getline(input_, line);
}

void IceCokeScriptCompilerDelegate::CompilerError(const ScriptCompilerError &error)
{
	switch (error.code)
	{
	case ScriptCompilerErrorCodeTainted:
		std::cout << "ERROR: Compiler tainted. " << std::endl;
		break;

	case ScriptCompilerErrorCodeNotImplemented:
		std::cout << "ERROR: Compiler state not implemented." << std::endl;
		break;

	case ScriptCompilerErrorCodeCreateAction:
		std::cout << "ERROR: Create action failed." << std::endl;
		PrintErrorLine(error);
		break;

	case ScriptCompilerErrorCodeSyntax:
		std::cout << "ERROR: Syntax error." << std::endl;
		PrintErrorLine(error);
		break;

	case ScriptCompilerErrorCodeUnexpectedEnd:
		std::cout << "ERROR: Unexpected end of script." << std::endl;
		break;

	default:
		std::cout << "ERROR: Unknown compiler error." << std::endl;
		PrintErrorLine(error);
		break;
	}
}

void IceCokeScriptCompilerDelegate::PrintErrorLine(const ScriptCompilerError &error)
{
	std::cout << error.lineNumber << " " << error.line << std::endl;
}
