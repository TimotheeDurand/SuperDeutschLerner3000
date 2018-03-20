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

void StateInitial::startTraining (Controller & controller, QFileInfo lessonFileInfo) const
{
	auto[lesson, status] = controller.getParser ().parseFile (lessonFileInfo);

	if (status == Parser::IOStatus::CANNOT_OPEN_FILE)
	{
		controller.getViewer ()->showFileError (lessonFileInfo);
	}
	else
	{
		controller.getViewer ()->showTrainingStarted (lessonFileInfo);
		controller.getStateTraining ()->createTrainingSession (controller, lesson);
		controller.setCurrentState (controller.getStateTraining ());
	}
}

void StateInitial::showLesson (Controller & controller, QFileInfo lessonFileInfo) const
{
	auto[lesson, status] = controller.getParser ().parseFile (lessonFileInfo);
	DictionnaryType dict = lesson.getDictionnary ();

	QVector<std::pair<QString, QString>> tuples;

	for (auto tuple : dict)
	{
		tuples.push_back ({ tuple.getOriginal (), tuple.getTranslated () });
	}

	controller.getViewer ()->showFullLesson (tuples);
}
