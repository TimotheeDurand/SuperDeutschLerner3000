#include "MainWindow.h"

#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow ()
{
	QVBoxLayout *layout = new QVBoxLayout (this);
	m_mainSplitter = new QSplitter (Qt::Horizontal, this);
	layout->addWidget (m_mainSplitter);

	m_lessonsListView = new QListView (m_mainSplitter);

	m_lessonListModel = new QStandardItemModel (this);
	m_lessonsListView->setModel (m_lessonListModel);

	m_wordsTable = new QTableView (m_mainSplitter);

	m_wordListModel = new QStandardItemModel (this);
	m_wordListModel->setHeaderData (OR_COL, Qt::Vertical, "German");
	m_wordListModel->setHeaderData (TR_COL, Qt::Vertical, "French");
	m_wordsTable->setModel (m_wordListModel);
}

void MainWindow::launchUserInterface ()
{
	this->show ();
}

void MainWindow::displayLessonList (QDir folder, QFileInfoList & lessonList)
{
	m_lessonListModel->clear ();
	
	for (auto lesson : lessonList)
	{
		QStandardItem *item = new QStandardItem(lesson.fileName ());
		item->setEditable (false);
		m_lessonListModel->appendRow (item);
	}
}

void MainWindow::showFileError (QFileInfo fileInfos)
{
	QMessageBox::warning (this, "File error", "Could not open file " + fileInfos.fileName ());
}

void MainWindow::showTrainingStarted (QFileInfo fileInfos)
{
	// todo : do something ? maybe some notification ?
}

void MainWindow::askWord (QString word, bool original)
{
	QStandardItem *item = new QStandardItem (word);
	item->setEditable (false);
	QStandardItem *itemEmpty = new QStandardItem ("");
	itemEmpty->setEditable (true);

	if(original)
		m_wordListModel->appendRow ({ item, itemEmpty });
	else
		m_wordListModel->appendRow ({ itemEmpty, item });

	lastAsked = new QModelIndex(m_wordListModel->indexFromItem (item));
	m_wordsTable->selectionModel ()->select (*lastAsked, QItemSelectionModel::ClearAndSelect);
}

void MainWindow::giveAnswer (QString originalWord, QString translatedWord, bool success)
{
	if (lastAsked)
	{
		QStandardItem *originalWordItem = m_wordListModel->item (lastAsked->row (), OR_COL);
		QStandardItem *translatedWordItem = m_wordListModel->item (lastAsked->row (), TR_COL);

		if (lastAsked->column () == OR_COL)
		{ // original
			originalWordItem->setData (originalWord);
			// maybe color it red or green for success / failure
		}
		else
		{ // translated
			translatedWordItem->setData (translatedWord);
			// maybe color it red or green for success / failure
		}
	}
}

void MainWindow::showTrainingEnded (int correctAnswers, int totalAnswers, QList<std::tuple<QString, QString, bool, QString>>& answers)
{
	// todo : do something ? maybe show stats ?
}
