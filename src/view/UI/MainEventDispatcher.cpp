#include "MainEventDispatcher.h"

#include <QDebug>

MainEventDispatcher::MainEventDispatcher (Controller* controller, GenericViewer* viewer)
	: GenericEventDispatcher (controller, viewer)
{
	m_mainWindow = dynamic_cast<MainWindow*>(viewer);
}

void MainEventDispatcher::onLessonSelectionChanged (const QItemSelection & selected, const QItemSelection & deselected)
{
	if (!selected.indexes().empty ())
	{
		m_mainWindow->disableTrainingButton (false);
		QStandardItem *item = m_mainWindow->getLessonModel ()->item (selected.indexes().first ().row());
		QString fileName = item->text ();
		if (!fileName.isEmpty ())
			m_controller->showLesson (fileName);
		QString displayFileName = m_controller->getFolderPath ().path () + "/" + fileName;
		m_mainWindow->setInfo ("file: " + displayFileName);
	}
	else
	{
		m_mainWindow->disableTrainingButton (true);
	}
}

void MainEventDispatcher::onLessonDoubleClicked (const QModelIndex & idx)
{
	m_mainWindow->disableTrainingButton (false);
	QStandardItem *item = m_mainWindow->getLessonModel ()->item (idx.row ());
	QString fileName = item->text ();
	if (!fileName.isEmpty ())
		m_controller->showLesson (fileName);
	QString displayFileName = m_controller->getFolderPath ().path () + "/" + fileName;
	m_mainWindow->setInfo ("file: " + displayFileName);
}

void MainEventDispatcher::onWordTableItemChanged (QStandardItem * item)
{
	if (m_mainWindow->getLastAskedIndex ())
	{
		m_controller->answer (item->text ());
	}
}

void MainEventDispatcher::onChangeFolderButtonClicked ()
{
	QDir newDir = m_mainWindow->openFileDialog (m_controller->getFolderPath ());
	if (!newDir.isEmpty ())
	{
		m_controller->selectNewLessonFolder (newDir);
	}
}

void MainEventDispatcher::onStartTrainingButtonClicked ()
{
	QStandardItem *item = m_mainWindow->getSelectedLesson ();
	QString fileName = item->text ();
	if (!fileName.isEmpty ())
		m_controller->startTraining (fileName);
}

void MainEventDispatcher::onStopTrainingButtonClicked ()
{
	m_controller->closeTraining ();
}
