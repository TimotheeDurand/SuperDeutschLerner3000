#pragma once

#include <list>
#include <string>

class GenericViewer
{
public:
	virtual void launchUserInterface () = 0;
	virtual void displayLessonList (std::string folderPath, std::list<std::string>& lessonList) = 0;

private:

};