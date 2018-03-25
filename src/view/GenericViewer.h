#pragma once

#include <QDir>

class GenericViewer
{
public:
	typedef enum {DIR_UNACCESSIBLE, CANNOT_OPEN, CANNOT_CREATE, CANNOT_DELETE, CANNOT_RENAME, CANNOT_WRITE} FileError;

	virtual void launchUserInterface () = 0;
	virtual void displayLessonList (QDir folder, QFileInfoList& lessonList) = 0;
	virtual void refreshLessonList (QDir folder, QFileInfoList& lessonList) = 0;
	virtual void showFileError (QFileInfo fileInfos, FileError error) = 0;
	virtual void showTrainingStarted (QFileInfo fileInfos) = 0;
	virtual void askWord (QString word, bool original) = 0;
	virtual void giveAnswer (QString originalWord, QString translatedWord, bool success) = 0;
	virtual void showTrainingEnded (int correctAnswers, int totalAnswers, QList<std::tuple<QString, QString, bool, QString>> &answers) = 0;
	virtual void showFullLesson (QFileInfo lessonFile, QVector<std::pair<QString, QString>> tuples) = 0;
	virtual void showEditingStarted (QFileInfo fileInfos, QVector<std::pair<QString, QString>> &tuples) = 0;
	virtual void showTupleInvalid (QString old_originalWord, QString old_translatedWord, int index) = 0;
	virtual void showTupleAdded (QString originalWord, QString translatedWord, int index) = 0;
	virtual void showRowDeleted (QString old_originalWord, QString old_translatedWord, int index) = 0;
	virtual void showLessonSaved (QFileInfo lessonFile) = 0;
	virtual void showLessonClosed (QFileInfo lessonFile) = 0;
	virtual void showFileCreated (QFileInfo lessonFile) = 0;
	virtual void showFileDeleted (QFileInfo lessonFile) = 0;

private:

};