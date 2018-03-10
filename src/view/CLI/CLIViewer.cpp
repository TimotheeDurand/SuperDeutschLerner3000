#include "CLIViewer.h"
#include <iostream>

using namespace std;

void CLIViewer::launchUserInterface ()
{
	cout << "SuperDeutschLerner3000 started. For a command list type \"help\"" << endl;

	cout << "SDL3k> ";

	while (listenKeyBoardInput ()) cout << "SDL3k> ";

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
	cout << "cd - change lesson directory" << endl;
	cout << "help - display command list" << endl;
	cout << "lessons (l) - show lessons in the current directory" << endl;
}

void CLIViewer::showUnknownCommand (std::string command)
{
	cout << "Unknown command: " << command << endl;
}

bool CLIViewer::listenKeyBoardInput ()
{
	std::string userInput;
	std::getline (std::cin, userInput);
	return eventDispatcher->handleUserInput (userInput);
}
