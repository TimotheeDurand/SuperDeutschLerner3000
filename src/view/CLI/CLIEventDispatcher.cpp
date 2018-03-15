#include "CLIEventDispatcher.h"
#include <QVector>
#include <QTextStream>

using namespace std;

CLIEventDispatcher::CLIEventDispatcher (Controller * controller, GenericViewer * viewer)
	: GenericEventDispatcher (controller, viewer)
{
	m_cliviewer = dynamic_cast<CLIViewer*>(viewer);
}

bool CLIEventDispatcher::handleUserInput (QString userInput)
{
	// Split user inputs as tokens
	QVector<QString> argv;
	char delimiter = ' ';
	int oldpos = 0;
	int pos = 0;
	do {
		pos = userInput.indexOf (delimiter, oldpos);
		argv.push_back (userInput.mid (oldpos, pos));
		oldpos = pos + 1;
	} while (pos != -1);

	// no arguments => ignore
	int argc = argv.size ();
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
