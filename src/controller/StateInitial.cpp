#include "StateInitial.h"
#include "StateTraining.h"

void StateInitial::selectNewLessonFolder (Controller & controller, QDir dir) const
{
	controller.setFolderPath (dir);
	QFileInfoList lessonList = controller.getParser ().listLessonsInFolder (dir);
	controller.getViewer ()->displayLessonList (dir, lessonList);
}

void StateInitial::showLessons (Controller & controller) const
{
	QFileInfoList lessonList = controller.getParser ().listLessonsInFolder (controller.getFolderPath ());
	controller.getViewer ()->displayLessonList (controller.getFolderPath (), lessonList);
}

void StateInitial::startTraining (Controller & controller, QFileInfo lessonFile) const
{
	auto[lesson, status] = controller.getParser ().parseFile (lessonFile);

	if (status == Parser::IOStatus::CANNOT_OPEN_FILE)
	{
		controller.getViewer ()->showFileError (lessonFile);
	}
	else
	{
		controller.getViewer ()->showTrainingStarted (lessonFile);
		controller.getStateTraining ()->createTrainingSession (controller, lesson);
		controller.setCurrentState (controller.getStateTraining ());
	}
}
