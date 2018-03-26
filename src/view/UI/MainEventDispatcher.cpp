#include "MainEventDispatcher.h"

#include <QDebug>
#include "LessonDelegate.h"

MainEventDispatcher::MainEventDispatcher (Controller* controller, GenericViewer* viewer)
	: GenericEventDispatcher (controller, viewer)
{
	m_mainWindow = dynamic_cast<MainWindow*>(viewer);
}

void MainEventDispatcher::onLessonSelectionChanged (const QItemSelection & selected, const QItemSelection & deselected)
{
	if (!selected.indexes().empty ())
	{
		onLessonSelected (selected.indexes ().first ());
	}
	else
	{
		m_mainWindow->disableLessonInteractionButtons (true);
		m_mainWindow->setNewLessonName("");
	}
}

void MainEventDispatcher::onLessonClicked (const QModelIndex & idx)
{
	onLessonSelected (idx);
}

void MainEventDispatcher::onLessonSelected (const QModelIndex & index)
{
	m_mainWindow->disableLessonInteractionButtons (false);
	QStandardItem *item = m_mainWindow->getLessonModel ()->item (index.row ());
	QString fileName = m_controller->getFolderPath ().absolutePath () + "/" + item->text ();
	if (!fileName.isEmpty ())
		m_controller->showLesson (fileName);
}

void MainEventDispatcher::onWordTableItemChanged (QStandardItem * item)
{
	if ((State*)m_controller->getStateTraining () == m_controller->getCurrentState ())
	{
		if (m_mainWindow->getLastAskedIndex ())
		{
			m_controller->answer (item->text ());
		}
	}
	else if ((State*)m_controller->getStateEditing () == m_controller->getCurrentState ())
	{
		if (m_mainWindow->dontListenEdit()) return;

		// if last row -> add word
		int row = item->index ().row();
		if (item->index ().row () == m_mainWindow->getWordModel ()->rowCount () - 1)
		{
			// check if both the word and its translation are typed in
			QStandardItem* itemToCheck = m_mainWindow->getWordModel ()->item (row, 1 - item->index ().column ());
			if (itemToCheck->text ().isEmpty ())
			{
				m_mainWindow->getTableView ()->setCurrentIndex (itemToCheck->index ());
				m_mainWindow->getTableView()->edit(itemToCheck->index ());
			}
			else
			{
				QString original = m_mainWindow->getWordModel ()->item (row, OR_COL)->text ();
				QString translated = m_mainWindow->getWordModel ()->item (row, TR_COL)->text ();
				m_controller->addNewTuple (original, translated);
			}
		}
		else
		//if not last row -> edit word
		{
			QString original = m_mainWindow->getWordModel ()->item (row, OR_COL)->text ();
			QString translated = m_mainWindow->getWordModel ()->item (row, TR_COL)->text ();
			m_controller->editTuple (item->index ().row(), original, translated);
		}
	}
}

void MainEventDispatcher::onLessonNameChanged (QString oldName, QString newName)
{
	m_mainWindow->setNewLessonName (newName);
	m_mainWindow->setLastLessonName (oldName);
	m_controller->renameLessonFile (m_controller->getFolderPath ().absolutePath () + "/" + oldName, newName);
}

void MainEventDispatcher::onChangeFolderButtonClicked ()
{
	QDir newDir = m_mainWindow->openFileDialog (m_controller->getFolderPath ());
	m_controller->selectNewLessonFolder (newDir);
}

void MainEventDispatcher::onStartTrainingButtonClicked ()
{
	QStandardItem *item = m_mainWindow->getSelectedLesson ();
	QString fileName = item->text ();
	if (!fileName.isEmpty ())
		m_controller->startTraining (m_controller->getFolderPath().absolutePath() + "/" + fileName);
}

void MainEventDispatcher::onStopTrainingButtonClicked ()
{
	m_controller->closeTraining ();
}

void MainEventDispatcher::onButtonCreateLessonClicked ()
{
	m_controller->createNewLessonFile ();
}

void MainEventDispatcher::onButtonDeleteLessonClicked ()
{
	QStandardItem *item = m_mainWindow->getSelectedLesson ();
	QString fileName = item->text ();
	if (!fileName.isEmpty ())
		m_controller->deleteLessonFile (m_controller->getFolderPath ().absolutePath () + "/" + fileName);
}

void MainEventDispatcher::onButtonStartEditingClicked ()
{
	QStandardItem *item = m_mainWindow->getSelectedLesson ();
	QString fileName = item->text ();
	if (!fileName.isEmpty ())
		m_controller->editLesson (m_controller->getFolderPath ().absolutePath () + "/" + fileName);
}

void MainEventDispatcher::onButtonCloseEditingClicked ()
{
	m_controller->closeLesson ();
}

void MainEventDispatcher::onButtonSaveLessonClicked ()
{
	m_controller->saveLesson ();
}

void MainEventDispatcher::onButtonDeleteRowClicked ()
{
	int row = m_mainWindow->getSelectedRow ();
	if (row != NO_ROW)
	{
		m_controller->deleteTuple (row);
	}
}
