#include "CLIEventDispatcher.h"
#include <vector>
#include <sstream>

using namespace std;

CLIEventDispatcher::CLIEventDispatcher (Controller * controller, GenericViewer * viewer)
	: GenericEventDispatcher (controller, viewer)
{
	m_cliviewer = dynamic_cast<CLIViewer*>(viewer);
}

bool CLIEventDispatcher::handleUserInput (std::string userInput)
{
	// Split user inputs as tokens
	vector<string> argv;
	char delimiter = ' ';
	size_t oldpos = 0;
	size_t pos = 0;
	do {
		pos = userInput.find (delimiter, oldpos);
		argv.push_back (userInput.substr (oldpos, pos));
		oldpos = pos + 1;
	} while (pos != std::string::npos);

	// no arguments => ignore
	size_t argc = argv.size ();
	if (argc == 0)
	{
		return true;
	}

	// if training, interpret the input as an answer
	if (m_controller->getCurrentState () == (State*)m_controller->getStateTraining ())
	{
		if (userInput == "STOP")
		{
			m_controller->closeTraining ();
			return true;
		}
		
		m_controller->answer (userInput);
		return true;
	}
	
	// if not training, interpret the input as a command
	if (argv[0] == "exit")
	{
		return false;
	}
	else if (argv[0] == "pwd")
	{
		m_cliviewer->showWorkingDirectory (m_controller->getFolderPath ());
		return true;
	}
	else if (argv[0] == "cd")
	{
		if (argc > 1)
		{
			m_controller->selectNewLessonFolder (argv[1]);
		}
		else
			m_cliviewer->showPathMissing ();
		return true;
	}
	else if (argv[0] == "help" || argv[0] == "h")
	{
		m_cliviewer->showCommandList ();
		return true;
	}
	else if (argv[0] == "lessons" || argv[0] == "ls")
	{
		m_controller->showLessons ();
		return true;
	}
	else if (argv[0] == "train" || argv[0] == "t")
	{
		if (argc > 1)
		{
			m_controller->startTraining (argv[1]);
			return true;
		}
		else
		{
			m_cliviewer->showFileMissing ();
			return true;
		}
	}
	else
	{
		m_cliviewer->showUnknownCommand (argv[0]);
	}

	return true;
}
