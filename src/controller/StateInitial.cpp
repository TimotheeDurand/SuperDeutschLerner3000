#include "StateInitial.h"
#include "StateTraining.h"

void StateInitial::selectNewLessonFolder (Controller & controller, std::string folderPath) const
{
	controller.setFolderPath (folderPath);
	std::list<std::string>& lessonList = controller.getParser ().listLessonsInFolder (folderPath);
	controller.getViewer ()->displayLessonList (folderPath, lessonList);
}

void StateInitial::showLessons (Controller & controller) const
{
	std::list<std::string>& lessonList = controller.getParser ().listLessonsInFolder (controller.getFolderPath ());
	controller.getViewer ()->displayLessonList (controller.getFolderPath (), lessonList);
}

void StateInitial::startTraining (Controller & controller, std::string lessonFileName) const
{
	auto[lesson, status] = controller.getParser ().parseFile (controller.getFolderPath () + '/' + lessonFileName);

	if (status == Parser::IOStatus::CANNOT_OPEN_FILE)
	{
		controller.getViewer ()->showFileError (lessonFileName);
	}
	else
	{
		controller.getViewer ()->showTrainingStarted (lessonFileName);
		controller.getStateTraining ()->createTrainingSession (controller, lesson);
		controller.setCurrentState (controller.getStateTraining ());
	}
}
