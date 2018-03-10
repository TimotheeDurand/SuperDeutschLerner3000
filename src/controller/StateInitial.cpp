#include "StateInitial.h"

void StateInitial::selectNewLessonFolder (Controller & controller, std::string folderPath) const
{
	controller.setFolderPath (folderPath);
	std::list<std::string>& lessonList = controller.getParser ().listLessonsInFolder (folderPath);
	controller.getViewer ()->displayLessonList (folderPath, lessonList);
}

void StateInitial::showLessons (Controller & controller) const
{
	std::list<std::string>& lessonList = controller.getParser ().listLessonsInFolder (controller.getFolderPath());
	controller.getViewer ()->displayLessonList (controller.getFolderPath (), lessonList);
}

void StateInitial::startTraining (Controller & controller, std::string lessonFileName) const
{
	//auto [lesson, status] = controller.getParser ().parseFile (controller.getFolderPath + lessonFileName);
	std::tuple<Lesson, Parser::IOStatus> test = controller.getParser ().parseFile (controller.getFolderPath + lessonFileName);
	

}
