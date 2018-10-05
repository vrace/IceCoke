#include <algorithm>

#include "ScriptCompiler.h"
#include "../Action/ActionFactory.h"

enum CompilerState
{
	CompilerStateStart,
	CompilerStateParameter,
	CompilerStateMultiLineParameter,
	CompilerStateComplete,
	CompilerStateError,
};

ScriptCompiler::ScriptCompiler(ScriptCompilerDelegate *delegate)
	: delegate_(delegate)
	, lineNumber_(0)
	, state_(CompilerStateStart)
	, script_(new Script())
	, action_(NULL)
	, errorCode_(ScriptCompilerErrorCodeUnknown)
{

}

ScriptCompiler::~ScriptCompiler()
{
	delete script_;
	delete action_;
}

Script* ScriptCompiler::Compile()
{
	if (!script_)
	{
		SetError(ScriptCompilerErrorCodeTainted);
		ProcessError();
		return NULL;
	}

	while (state_ != CompilerStateComplete)
	{
		switch (state_)
		{
		case CompilerStateStart:
			ProcessStart();
			break;

		case CompilerStateParameter:
			ProcessParameter();
			break;

		case CompilerStateMultiLineParameter:
			ProcessMultiLineParameter();
			break;

		case CompilerStateError:
			ProcessError();
			return NULL;

		default:
			SetError(ScriptCompilerErrorCodeNotImplemented);
			break;
		}
	}

	Script *s = script_;
	script_ = NULL;

	return s;
}

void ScriptCompiler::SetError(ScriptCompilerErrorCode errorCode)
{
	errorCode_ = errorCode;
	state_ = CompilerStateError;
}

void ScriptCompiler::ProcessStart()
{
	lineNumber_++;

	if (!delegate_->NextLine(line_))
	{
		state_ = CompilerStateComplete;
		return;
	}

	if (line_.empty() || line_[0] == '#' || line_ == "%%")
		return;

	action_ = ActionFactory::GetInstance()->CreateAction(line_);
	if (!action_)
	{
		SetError(ScriptCompilerErrorCodeCreateAction);
		return;
	}

	state_ = CompilerStateParameter;
}

void ScriptCompiler::ProcessParameter()
{
	lineNumber_++;

	if (!delegate_->NextLine(line_))
	{
		state_ = CompilerStateComplete;
		CommitAction();
		return;
	}

	if (line_.empty() || line_[0] == '#')
		return;

	if (line_ == "%%")
	{
		state_ = CompilerStateStart;
		CommitAction();
		return;
	}

	std::string::size_type pos = line_.find(":");
	if (pos == std::string::npos)
	{
		SetError(ScriptCompilerErrorCodeSyntax);
		return;
	}

	std::string name = line_.substr(0, pos);
	std::string value = line_.substr(pos + 1);

	pos = value.find_first_not_of(' ');
	if (pos != std::string::npos)
		value = value.substr(pos);

	if (value == "@@")
	{
		multiLineName_ = name;
		multiLineValue_ = "";
		state_ = CompilerStateMultiLineParameter;
	}
	else
	{
		action_->SetParameter(ActionParameter(name, value));
	}
}

void ScriptCompiler::ProcessMultiLineParameter()
{
	lineNumber_++;

	if (!delegate_->NextLine(line_))
	{
		SetError(ScriptCompilerErrorCodeUnexpectedEnd);
		return;
	}

	if (line_ == "@@")
	{
		action_->SetParameter(ActionParameter(multiLineName_, multiLineValue_));
		state_ = CompilerStateParameter;
		return;
	}

	if (!multiLineValue_.empty())
		multiLineValue_ += "\n";

	multiLineValue_ += line_;
}

void ScriptCompiler::ProcessError()
{
	delegate_->CompilerError(ScriptCompilerError(errorCode_, lineNumber_, line_));
}

void ScriptCompiler::CommitAction()
{
	if (action_)
	{
		script_->AppendAction(action_);
		action_ = NULL;
	}
}
