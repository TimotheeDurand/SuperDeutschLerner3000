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
	void onLessonDoubleClicked (const QModelIndex &idx);
	void onWordTableItemChanged (QStandardItem* item);
	void onChangeFolderButtonClicked ();
	void onStartTrainingButtonClicked ();
	void onStopTrainingButtonClicked ();

private:
	MainWindow * m_mainWindow;
};