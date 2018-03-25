#pragma once

#include "src\view\GenericEventDispatcher.h"
#include "MainWindow.h"

#include <QObject>

class MainWindow;

class MainEventDispatcher : public QObject, public GenericEventDispatcher
{
	Q_OBJECT
public:
	MainEventDispatcher (Controller* controller, GenericViewer* viewer);

public slots:
	void onLessonSelectionChanged (const QItemSelection & selected, const QItemSelection & deselected);
	void onLessonClicked (const QModelIndex &idx);
	void onWordTableItemChanged (QStandardItem* item);
	void onLessonNameChanged (QString oldName, QString newName);
	void onChangeFolderButtonClicked ();
	void onStartTrainingButtonClicked ();
	void onStopTrainingButtonClicked ();
	void onButtonCreateLessonClicked ();
	void onButtonDeleteLessonClicked ();
	void onButtonStartEditingClicked ();
	void onButtonCloseEditingClicked ();
	void onButtonSaveLessonClicked ();
	void onButtonDeleteRowClicked ();

private:
	void onLessonSelected (const QModelIndex & index);
	MainWindow * m_mainWindow;
};