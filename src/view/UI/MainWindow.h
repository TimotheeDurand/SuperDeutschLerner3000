#pragma once

#include <QWidget>
#include <QListView>
#include <QSplitter>
#include <QTableView>
#include <QStandardItemModel>

#include "src\view\GenericViewer.h"
#include "MainEventDispatcher.h"

#define OR_COL 0
#define TR_COL 1

class MainEventDispatcher;

class MainWindow : public QWidget, public GenericViewer
{
	Q_OBJECT

public:
	MainWindow ();
	void setEventDispatcher (MainEventDispatcher* dispatcher);
	virtual void launchUserInterface () override;
	virtual void displayLessonList (QDir folder, QFileInfoList& lessonList) override;
	virtual void showFileError (QFileInfo fileInfos) override;
	virtual void showTrainingStarted (QFileInfo fileInfos) override;
	virtual void askWord (QString word, bool original) override;
	virtual void giveAnswer (QString originalWord, QString translatedWord, bool success) override;
	virtual void showTrainingEnded (int correctAnswers, int totalAnswers, QList<std::tuple<QString, QString, bool, QString>> &answers) override;

	QStandardItemModel* getLessonModel () { return m_lessonListModel; }

private:
	QListView *m_lessonsListView;
	QSplitter *m_mainSplitter;
	QTableView *m_wordsTable;
	QStandardItemModel *m_lessonListModel;
	QStandardItemModel *m_wordListModel;

	MainEventDispatcher *m_eventDispatcher;

	QModelIndex *lastAsked = NULL;

};