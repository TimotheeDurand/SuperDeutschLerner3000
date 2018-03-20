#pragma once

#include <QWidget>
#include <QListView>
#include <QSplitter>
#include <QTableView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QLabel>

#include "src\view\GenericViewer.h"
#include "MainEventDispatcher.h"
#include "CompressibleLabel.h"

#define OR_COL 0
#define TR_COL 1
#define TRAIN_COLOR_BG "#ca5100"
#define TRAIN_COLOR_FG "#ffb17c"
#define DEFAULT_COLOR_BG "#014b7c"
#define DEFAULT_COLOR_FG "#79c8fc"
#define FINISHED_COLOR_BG "#017c0f"
#define FINISHED_COLOR_FG "#7fff8e"

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
	virtual void showFullLesson (QVector<std::pair<QString, QString>> tuples) override;

	QDir openFileDialog (QDir dir);

	void disableTrainingButton (bool disable) { m_startTrainingButton->setDisabled (disable); }
	void setInfo (const QString &info);
	void setInfoWord (const QString &infoWords);
	void setInfoScore (const QString &infoScore);
	void setInfoScore (int correct, int incorrect);
	void setDownRibbonColor (const QColor &color, const QColor & colorFG);

	QStandardItemModel* getLessonModel () { return m_lessonListModel; }
	QModelIndex* getLastAskedIndex () { return lastAsked; }

	QStandardItem* getSelectedLesson ();

private:
	void resetTableAndInfo ();

	QListView *m_lessonsListView;
	QSplitter *m_mainSplitter;
	QTableView *m_wordsTable;
	QStandardItemModel *m_lessonListModel;
	QStandardItemModel *m_wordListModel;

	CompressibleLabel *m_folderNameLabel;

	QLabel *m_infoLabel;
	QLabel *m_infoWordsLabel;
	QLabel *m_infoScoreLabel;

	QPushButton *m_changeFolderButton;
	QPushButton *m_startTrainingButton;
	QPushButton *m_stopTrainingButton;

	MainEventDispatcher *m_eventDispatcher;

	QModelIndex *lastAsked = nullptr;

	// Variable used to keep track of user score
	int askedWordCount = 0;
	int currentWordCount = 0;
	int correctWordsCount = 0;
};