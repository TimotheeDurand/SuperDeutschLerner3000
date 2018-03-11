#include "CLIViewer.h"
#include <iostream>
#include <iomanip>

using namespace std;

void CLIViewer::launchUserInterface ()
{
	cout << "SuperDeutschLerner3000 started. For a command list type \"help\"" << endl << endl;

	cout << "SDL3k> ";

	while (listenKeyBoardInput ()) cout << endl << "SDL3k> ";

	cout << "bye" << endl;
}

void CLIViewer::displayLessonList (std::string folderPath, std::list<std::string>& lessonList)
{
	cout << "displaying lessons in: " << folderPath << endl;
	for (auto it : lessonList)
	{
		cout << it << endl;
	}
}

void CLIViewer::showCommandList ()
{
	int cmdw = 25;
	cout << setw (cmdw) << left << "cd [dir]" << " - change current working directory to [dir]" << endl;
	cout << setw (cmdw) << left << "help (h)" << " - display command list" << endl;
	cout << setw (cmdw) << left << "lessons (ls)" << " - show lessons in the current directory" << endl;
	cout << setw (cmdw) << left << "train (t) [file.les]" << " - start a training session on the [file.les]" << endl;
}

void CLIViewer::showUnknownCommand (std::string command)
{
	cout << "Unknown command: " << command << endl;
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
	cout << "Error : could not open file " << fileName << endl;
}

void CLIViewer::showTrainingStarted (std::string fileName)
{
	cout << "Training started on file : " << fileName << endl;
	cout << "To stop training, type \"STOP\"" << endl << endl;
}

void CLIViewer::showTrainingEnded (int correctAnswers, int totalAnswers)
{
	cout << "Training session over !" << endl;
	cout << "Correct answers : " << correctAnswers << endl;
	cout << "Errors : " << totalAnswers << endl;
}

void CLIViewer::giveAnswer (std::string originalWord, std::string translatedWord, bool success)
{
	if (success)
		cout << originalWord << " : " << translatedWord << " CORRECT" << endl;
	else
		cout << originalWord << " : " << translatedWord << " INCORRECT" << endl;
	cout << endl;
}

void CLIViewer::askWord (std::string word)
{
	cout << "Type the meaning of : " << word << endl;
}

bool CLIViewer::listenKeyBoardInput ()
{
	std::string userInput;
	std::getline (std::cin, userInput);
	cout << endl;
	return eventDispatcher->handleUserInput (userInput);
}
