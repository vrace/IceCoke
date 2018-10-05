#ifndef ICE_COKE_SCRIPT_COMPILER_DELEGATE_H
#define ICE_COKE_SCRIPT_COMPILER_DELEGATE_H

#include <iostream>

#include "Scripting/ScriptCompilerDelegate.h"

class IceCokeScriptCompilerDelegate : public ScriptCompilerDelegate
{
public:
	IceCokeScriptCompilerDelegate(std::istream &input);

	bool NextLine(std::string &line);
	void CompilerError(const ScriptCompilerError &error);

private:
	IceCokeScriptCompilerDelegate();
	IceCokeScriptCompilerDelegate(const IceCokeScriptCompilerDelegate&);
	IceCokeScriptCompilerDelegate& operator=(const IceCokeScriptCompilerDelegate&);

	void PrintErrorLine(const ScriptCompilerError &error);

private:
	std::istream &input_;
};

#endif
