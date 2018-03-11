#pragma once

#include <list>
#include <string>

class GenericViewer
{
public:
	virtual void launchUserInterface () = 0;
	virtual void displayLessonList (std::string folderPath, std::list<std::string>& lessonList) = 0;
	virtual void showFileError (std::string fileName) = 0;
	virtual void showTrainingStarted (std::string fileName) = 0;
	virtual void askWord (std::string word) = 0;
	virtual void giveAnswer (std::string originalWord, std::string translatedWord, bool success) = 0;
	virtual void showTrainingEnded (int correctWords, int totalWords) = 0;

private:

};