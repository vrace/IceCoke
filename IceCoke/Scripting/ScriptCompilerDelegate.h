#ifndef SCRIPT_COMPILER_DELEGATE_H
#define SCRIPT_COMPILER_DELEGATE_H

#include <string>
#include "ScriptCompilerError.h"

class ScriptCompilerDelegate
{
public:
	virtual ~ScriptCompilerDelegate() {}
	virtual bool NextLine(std::string &line) = 0;
	virtual void CompilerError(const ScriptCompilerError &error) = 0;
};

#endif
