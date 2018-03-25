#include "StateInitial.h"
#include "StateTraining.h"
#include "StateEditing.h"

#include <QDebug> // to be removed

void StateInitial::selectNewLessonFolder (Controller & controller, QDir dir) const
{
	if (dir.exists () && dir.isReadable ())
	{
		controller.setFolderPath (dir);
		QFileInfoList lessonList = controller.getParser ().listLessonsInFolder (dir);
		controller.getViewer ()->displayLessonList (dir, lessonList);
	}
	else
	{
		controller.getViewer ()->showFileError (dir.absolutePath (), GenericViewer::DIR_UNACCESSIBLE);
	}
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
		controller.getViewer ()->showFileError (lessonFileInfo, GenericViewer::CANNOT_OPEN);
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

	if (status == Parser::IOStatus::CANNOT_OPEN_FILE)
	{
		controller.getViewer ()->showFileError (lessonFileInfo, GenericViewer::CANNOT_OPEN);
	}
	else
	{
		DictionnaryType dict = lesson.getDictionnary ();
		QVector<std::pair<QString, QString>> tuples;
		for (auto tuple : dict)
		{
			tuples.push_back ({ tuple.getOriginal (), tuple.getTranslated () });
		}
		controller.getViewer ()->showFullLesson (lessonFileInfo, tuples);
	}
}

void StateInitial::createNewLessonFile (Controller & controller) const
{
	QString baseFileName = "newLesson";
	QString fileName = baseFileName;
	QString fileExtension = QString (DEFAULT_LESSON_FILE_EXTENSION);
	QFileInfoList lessonFiles = controller.getParser ().listLessonsInFolder (controller.getFolderPath ());

	QFileInfo check_file (controller.getFolderPath ().absolutePath () + "/" + fileName + fileExtension);

	int i = 1;
	while (check_file.exists () && check_file.isFile ())
	{
		fileName = baseFileName + QString::number (i);
		check_file = controller.getFolderPath ().absolutePath () + "/" + fileName + fileExtension;
		i++;
	}

	QFile newFile(controller.getFolderPath ().absolutePath () + "/" + fileName + fileExtension);

	if (newFile.open (QIODevice::WriteOnly))
	{
		//write something ?
		controller.getViewer ()->showFileCreated (check_file);
		controller.refreshLessons ();
	}
	else
	{
		controller.refreshLessons ();
		controller.getViewer ()->showFileError (check_file, GenericViewer::CANNOT_CREATE);
	}
}

void StateInitial::renameLessonFile (Controller & controller, QFileInfo lessonFileInfo, QString newName) const
{
	QFile file (lessonFileInfo.filePath());
	QString newNameFull = controller.getFolderPath ().absolutePath () + "/" + newName;
	if (file.exists () && file.rename (newNameFull))
	{
		controller.refreshLessons ();
	}
	else
	{
		controller.getViewer ()->showFileError (lessonFileInfo, GenericViewer::CANNOT_RENAME);
	}
}

void StateInitial::deleteLessonFile (Controller & controller, QFileInfo lessonFileInfo) const
{
	QString res = controller.getParser ().MoveFileToTrash (lessonFileInfo);

	if (res.isEmpty ())
	{
		controller.refreshLessons ();
		controller.getViewer ()->showFileDeleted (lessonFileInfo);
	}
	else
	{
		controller.getViewer ()->showFileError (lessonFileInfo, GenericViewer::CANNOT_DELETE);
	}
}

void StateInitial::refreshLessons (Controller & controller) const
{
	QFileInfoList lessonList = controller.getParser ().listLessonsInFolder (controller.getFolderPath ());
	controller.getViewer ()->refreshLessonList (controller.getFolderPath (), lessonList);
}

void StateInitial::editLesson (Controller & controller, QFileInfo lessonFileInfo) const
{
	auto[lesson, status] = controller.getParser ().parseFile (lessonFileInfo);

	if (status == Parser::IOStatus::CANNOT_OPEN_FILE)
	{
		controller.getViewer ()->showFileError (lessonFileInfo, GenericViewer::CANNOT_OPEN);
	}
	else
	{
		DictionnaryType dict = lesson.getDictionnary ();
		QVector<std::pair<QString, QString>> tuples;
		tuples.reserve (dict.size ());
		for (auto tuple : dict)
		{
			tuples.push_back ({ tuple.getOriginal (), tuple.getTranslated () });
		}
		controller.getViewer ()->showEditingStarted (lessonFileInfo, tuples);
		controller.setEditedLessonFileInfo (lessonFileInfo);
		controller.setEditedLesson (new Lesson (lesson));
		controller.setCurrentState (controller.getStateEditing ());
	}
}
