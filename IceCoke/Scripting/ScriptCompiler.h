#ifndef SCRIPT_COMPILER_H
#define SCRIPT_COMPILER_H

#include "Script.h"
#include "ScriptCompilerError.h"
#include "ScriptCompilerDelegate.h"

enum CompilerState;

class ScriptCompiler
{
public:
	ScriptCompiler(ScriptCompilerDelegate *delegate);
	~ScriptCompiler();

	Script* Compile();

private:
	ScriptCompiler(const ScriptCompiler&);
	ScriptCompiler& operator=(const ScriptCompiler&);

	void SetError(ScriptCompilerErrorCode errorCode);
	void CommitAction();

	void ProcessStart();
	void ProcessParameter();
	void ProcessMultiLineParameter();
	void ProcessError();

private:
	ScriptCompilerDelegate *delegate_;
	Script *script_;
	Action *action_;
	std::string line_;
	int lineNumber_;
	CompilerState state_;
	ScriptCompilerErrorCode errorCode_;
	std::string multiLineName_;
	std::string multiLineValue_;
};

#endif
