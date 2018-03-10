#pragma once

#include "src\view\GenericViewer.h"
#include "CLIEventDispatcher.h"

class CLIEventDispatcher;

class CLIViewer : public GenericViewer
{
public:
	virtual void launchUserInterface () override;
	virtual void displayLessonList (std::string folderPath, std::list<std::string>& lessonList) override;
	void setEventDispatcher (CLIEventDispatcher* dispatcher) { eventDispatcher = dispatcher; }
	void showCommandList ();
	void showUnknownCommand (std::string command);

private:
	bool listenKeyBoardInput ();

	CLIEventDispatcher* eventDispatcher;

};