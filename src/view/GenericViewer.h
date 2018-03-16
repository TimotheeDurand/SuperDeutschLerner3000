#pragma once

#include <QDir>

class GenericViewer
{
public:
	virtual void launchUserInterface () = 0;
	virtual void displayLessonList (QDir folder, QFileInfoList& lessonList) = 0;
	virtual void showFileError (QFileInfo fileInfos) = 0;
	virtual void showTrainingStarted (QFileInfo fileInfos) = 0;
	virtual void askWord (QString word, bool original) = 0;
	virtual void giveAnswer (QString originalWord, QString translatedWord, bool success) = 0;
	virtual void showTrainingEnded (int correctAnswers, int totalAnswers, QList<std::tuple<QString, QString, bool, QString>> &answers) = 0;

private:

};