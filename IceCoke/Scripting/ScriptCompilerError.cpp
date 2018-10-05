#include "ScriptCompilerError.h"

ScriptCompilerError::ScriptCompilerError()
	: code(ScriptCompilerErrorCodeUnknown)
	, lineNumber(0)
{

}

ScriptCompilerError::ScriptCompilerError(ScriptCompilerErrorCode code_, int lineNumber_, const std::string &line_)
	: code(code_)
	, lineNumber(lineNumber_)
	, line(line_)
{

}
