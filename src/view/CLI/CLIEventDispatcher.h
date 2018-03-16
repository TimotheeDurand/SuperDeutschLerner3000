#pragma once

#include "src\view\GenericEventDispatcher.h"
#include "CLIViewer.h"

class CLIViewer;

class CLIEventDispatcher : public GenericEventDispatcher
{
public:
	CLIEventDispatcher (Controller* controller, GenericViewer* viewer);
		
	bool handleUserInput (QString userInput);

private:
	CLIViewer * m_cliviewer;
};