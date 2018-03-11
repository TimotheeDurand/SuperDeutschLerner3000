#include "CLIViewer.h"
#include <iostream>
#include <iomanip>
#include <libs\rang.hpp>

using namespace std;
using namespace rang;

void CLIViewer::launchUserInterface ()
{
	cout << "SuperDeutschLerner3000 started. For a command list type \"help\"" << endl << endl;

	cout << fg::yellow << "SDL3k> " << fg::reset;

	while (listenKeyBoardInput ()) cout << endl << fg::yellow << "SDL3k> " << fg::reset;

	cout << "bye" << endl;
}

void CLIViewer::displayLessonList (std::string folderPath, std::list<std::string>& lessonList)
{
	cout << "displaying lessons in: " << folderPath << endl << endl;
	for (auto it : lessonList)
	{
		cout << it << endl;
	}
}

void CLIViewer::showCommandList ()
{
	int cmdw = 25;
	cout << setw (cmdw) << left << "pwd" << " - show the current working directory" << endl;
	cout << setw (cmdw) << left << "cd [dir]" << " - change current working directory to [dir]" << endl;
	cout << setw (cmdw) << left << "help (h)" << " - display command list" << endl;
	cout << setw (cmdw) << left << "lessons (ls)" << " - show lessons in the current directory" << endl;
	cout << setw (cmdw) << left << "train (t) [file.les]" << " - start a training session on the [file.les]" << endl;
	cout << setw (cmdw) << left << "exit" << " - exit SDL3k" << endl;
}

void CLIViewer::showWorkingDirectory (std::string workingDirectory)
{
	cout << workingDirectory << endl;
}

void CLIViewer::showUnknownCommand (std::string command)
{
	cout << "Unknown command: \'" << command << '\'' << endl;
}

void CLIViewer::showPathMissing ()
{
	cout << "Please provide a path" << endl;
}

void CLIViewer::showFileMissing ()
{
	cout << "Please provide a lesson file name" << endl;
}

void CLIViewer::showFileError (std::string fileName)
{
	cout << fg::red << "Error" << fg::reset << " : could not open file \'" << fileName << '\''<< endl;
}

void CLIViewer::showTrainingStarted (std::string fileName)
{
	cout << fg::green << "TRAINING STARTED" << fg::reset << endl;
	cout << "To stop training, type \"STOP\"" << endl;
	cout << "lesson selected : " << fileName << endl;
	cout << fg::green << "GOOD LUCK" << fg::reset << endl << endl;
}

void CLIViewer::showTrainingEnded (int correctAnswers, int totalAnswers)
{
	cout << fg::green << "TRAINING SESSION OVER" << fg::reset << endl;
	cout << "Correct answers: " << fg::green << setw(4) << correctAnswers << fg::reset << endl;
	cout << "Errors: " << fg::red << setw(9+4) << (totalAnswers - correctAnswers) << fg::reset << endl;
}

void CLIViewer::giveAnswer (std::string originalWord, std::string translatedWord, bool success)
{
	if (success)
		cout << originalWord << " : " << translatedWord << fg::green << " CORRECT" << fg::reset << endl;
	else
		cout << originalWord << " : " << translatedWord << fg::red << " INCORRECT" << fg::reset << endl;
	cout << endl;
}

void CLIViewer::askWord (std::string word)
{
	cout << "What's the meaning of : \"" << word << '\"' << endl;
}

bool CLIViewer::listenKeyBoardInput ()
{
	std::string userInput;
	std::getline (std::cin, userInput);
	cout << endl;
	return eventDispatcher->handleUserInput (userInput);
}
