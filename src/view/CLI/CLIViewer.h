#pragma once

#include "src\view\GenericViewer.h"
#include "CLIEventDispatcher.h"

#include <QTextStream>
#include <stdio.h>

class CLIEventDispatcher;

class CLIViewer : public GenericViewer
{
public:
	CLIViewer ();
	virtual void launchUserInterface () override;
	virtual void displayLessonList (QDir folder, QFileInfoList& lessonList) override;
	virtual void refreshLessonList (QDir folder, QFileInfoList& lessonList) override;
	virtual void showFullLesson (QFileInfo lessonFile, QVector<std::pair<QString, QString>> tuples);
	void setEventDispatcher (CLIEventDispatcher* dispatcher) { eventDispatcher = dispatcher; }
	void showCommandList ();
	void showWorkingDirectory (QDir dir);
	void showUnknownCommand (QString command);
	void showPathMissing ();
	void showFileMissing ();
	virtual void showFileError (QFileInfo fileInfos, FileError error) override;
	virtual void showTrainingStarted (QFileInfo fileInfos) override;
	virtual void showTrainingEnded (int correctAnswers, int totalAnswers, QList<std::tuple<QString, QString, bool, QString>> &answers) override;
	virtual void giveAnswer (QString originalWord, QString translatedWord, bool success) override;
	virtual void askWord (QString word, bool original) override;
	virtual void showEditingStarted (QFileInfo fileInfos, QVector<std::pair<QString, QString>> &tuples) override;
	virtual void showTupleInvalid (QString old_originalWord, QString old_translatedWord, int index) override;
	virtual void showLessonSaved (QFileInfo lessonFile) override;
	virtual void showLessonClosed (QFileInfo lessonFile) override;
	virtual void showTupleAdded (QString originalWord, QString translatedWord, int index) override;
	virtual void showRowDeleted (QString old_originalWord, QString old_translatedWord, int index) override;
	virtual void showFileCreated (QFileInfo lessonFile) override;
	virtual void showFileDeleted (QFileInfo lessonFile) override;

private:
	bool listenKeyBoardInput ();
	void utf8Print (QString string);
	QString readLine ();
	CLIEventDispatcher* eventDispatcher;
	QTextStream cout; 
	QTextStream cin;

};