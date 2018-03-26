#pragma once

#include <QWidget>
#include <QListView>
#include <QSplitter>
#include <QTableView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QLabel>

#include "src\view\GenericViewer.h"
#include "MainEventDispatcher.h"
#include "CompressibleLabel.h"
#include "LessonDelegate.h"

#define OR_COL 0
#define TR_COL 1
#define NO_ROW -1
#define TRAIN_COLOR_BG "#ca5100"
#define TRAIN_COLOR_FG "#ffb17c"
#define DEFAULT_COLOR_BG "#014b7c"
#define DEFAULT_COLOR_FG "#79c8fc"
#define FINISHED_COLOR_BG "#017c0f"
#define FINISHED_COLOR_FG "#7fff8e"
#define EDITING_COLOR_BG "#5d009b"
#define EDITING_COLOR_FG "#dca8ff"

class MainEventDispatcher;

class MainWindow : public QWidget, public GenericViewer
{
	Q_OBJECT

public:
	MainWindow ();
	void setEventDispatcher (MainEventDispatcher* dispatcher);
	virtual void launchUserInterface () override;
	virtual void displayLessonList (QDir folder, QFileInfoList& lessonList) override;
	virtual void refreshLessonList (QDir folder, QFileInfoList& lessonList) override;
	virtual void showFileError (QFileInfo fileInfos, FileError error) override;
	virtual void showTrainingStarted (QFileInfo fileInfos) override;
	virtual void askWord (QString word, bool original) override;
	virtual void giveAnswer (QString originalWord, QString translatedWord, bool success) override;
	virtual void showTrainingEnded (int correctAnswers, int totalAnswers, QList<std::tuple<QString, QString, bool, QString>> &answers) override;
	virtual void showFullLesson (QFileInfo lessonFile, QVector<std::pair<QString, QString>> tuples) override;
	virtual void showEditingStarted (QFileInfo fileInfos, QVector<std::pair<QString, QString>>& tuples) override;
	virtual void showTupleInvalid (QString old_originalWord, QString old_translatedWord, int idx) override;
	virtual void showTupleAdded (QString originalWord, QString translatedWord, int index) override;
	virtual void showRowDeleted (QString old_originalWord, QString old_translatedWord, int index) override;
	virtual void showLessonSaved (QFileInfo lessonFile) override;
	virtual void showLessonClosed (QFileInfo lessonFile) override;
	virtual void showFileCreated (QFileInfo lessonFile) override;
	virtual void showFileDeleted (QFileInfo lessonFile) override;
	
	QString getLastLessonName () { return m_lastLessonName; }
	QString getNewLessonName () { return m_newLessonName; }
	void setNewLessonName (QString name) { m_newLessonName = name; }
	void setLastLessonName (QString name) { m_lastLessonName = name; }

	QDir openFileDialog (QDir dir);
	void disableLessonInteractionButtons (bool disable);
	bool dontListenEdit () { return m_dontListenEdit; }

	QStandardItemModel* getWordModel () { return m_wordListModel; }
	QStandardItemModel* getLessonModel () { return m_lessonListModel; }
	QTableView* getTableView () { return m_wordsTable; }

	int getSelectedRow ();
	QModelIndex* getLastAskedIndex () { return lastAsked; }
	QStandardItem* getSelectedLesson ();

	QMessageBox::StandardButton shouldWeSave (bool canCancel);

protected:
	void closeEvent (QCloseEvent *event);

	void setInfo (const QString &info);
	void setInfoWord (const QString &infoWords);
	void setInfoScore (const QString &infoScore);
	void setInfoScore (int correct, int incorrect);
	void setDownRibbonColor (const QColor &color, const QColor & colorFG);
	void resetTableAndInfo ();

	QListView *m_lessonsListView;
	QSplitter *m_mainSplitter;
	QTableView *m_wordsTable;
	QStandardItemModel *m_lessonListModel;
	LessonDelegate* m_lessonDelegate;
	QStandardItemModel *m_wordListModel;

	CompressibleLabel *m_folderNameLabel;

	QLabel *m_infoLabel;
	QLabel *m_infoWordsLabel;
	QLabel *m_infoScoreLabel;

	QPushButton *m_changeFolderButton;
	QPushButton *m_startTrainingButton;
	QPushButton *m_stopTrainingButton;
	QPushButton *m_createLessonButton;
	QPushButton *m_deleteLessonButton;
	QPushButton *m_editLessonButton;
	QPushButton *m_closeLessonButton;
	QPushButton *m_saveLessonButton;
	QPushButton *m_deleteRowButton;

	MainEventDispatcher *m_eventDispatcher;

	QModelIndex *lastAsked = nullptr;

	// Variable used to keep track of user score
	int m_askedWordCount = 0;
	int m_currentWordCount = 0;
	int m_correctWordsCount = 0;

	// Variable used to keep track of names during renaming operation
	QString m_lastLessonName = "";
	QString m_newLessonName = "";

	bool m_dontListenEdit = false;
	
	// variable used to keep track of editing
	bool m_modified = false;
};