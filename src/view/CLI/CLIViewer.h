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
	void showPathMissing ();
	void showFileMissing ();
	virtual void showFileError (std::string fileName) override;
	virtual void showTrainingStarted (std::string fileName) override;
	virtual void showTrainingEnded (int correctAnswers, int totalAnswers) override;
	virtual void giveAnswer (std::string originalWord, std::string translatedWord, bool success) override;
	virtual void askWord (std::string word) override;

private:
	bool listenKeyBoardInput ();

	CLIEventDispatcher* eventDispatcher;

};