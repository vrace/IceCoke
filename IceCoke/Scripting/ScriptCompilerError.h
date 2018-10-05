#ifndef SCRIPT_COMPILER_ERROR_H
#define SCRIPT_COMPILER_ERROR_H

#include <string>

enum ScriptCompilerErrorCode
{
	ScriptCompilerErrorCodeUnknown,
	ScriptCompilerErrorCodeTainted,
	ScriptCompilerErrorCodeNotImplemented,
	ScriptCompilerErrorCodeCreateAction,
	ScriptCompilerErrorCodeSyntax,
	ScriptCompilerErrorCodeUnexpectedEnd,
};

struct ScriptCompilerError
{
	ScriptCompilerError();
	ScriptCompilerError(ScriptCompilerErrorCode code, int lineNumber, const std::string &line);

	ScriptCompilerErrorCode code;
	int lineNumber;
	std::string line;
};

#endif
