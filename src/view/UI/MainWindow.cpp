#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>
#include <QTextStream>

#include <QDebug>

MainWindow::MainWindow ()
{
	// reading CSS from file
	QFile file (":/styles/MainWindow.css");
	if (file.open (QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream stream (&file);
		setStyleSheet (stream.readAll ());
		file.close ();
	}
	this->resize (1000, 500);
	this->setObjectName ("MainWindow");

	QHBoxLayout *layout = new QHBoxLayout (this);
	layout->setContentsMargins (0, 0, 0, 0);
	layout->setSpacing (0);

	QVBoxLayout *leftRibbonLayout = new QVBoxLayout ();
	layout->addLayout (leftRibbonLayout);
	leftRibbonLayout->setAlignment (Qt::AlignTop);
	layout->setContentsMargins (0, 0, 0, 0);

	m_changeFolderButton = new QPushButton (this);
	m_changeFolderButton->setObjectName ("ChangeFolder");
	leftRibbonLayout->addWidget (m_changeFolderButton);

	m_mainSplitter = new QSplitter (Qt::Horizontal, this);
	//m_mainSplitter->setOpaqueResize (false);
	layout->addWidget (m_mainSplitter);

	QWidget *folderLayoutContainer = new QWidget (m_mainSplitter);
	QVBoxLayout *folderDisplayLayout = new QVBoxLayout (folderLayoutContainer);
	folderDisplayLayout->setContentsMargins (0, 0, 0, 0);
	
	m_folderNameLabel = new CompressibleLabel (m_mainSplitter);
	m_folderNameLabel->setObjectName ("DirLabel");
	folderDisplayLayout->addWidget (m_folderNameLabel);
	
	m_lessonsListView = new QListView (m_mainSplitter);
	folderDisplayLayout->addWidget (m_lessonsListView);
	folderDisplayLayout->setStretchFactor (m_lessonsListView, 1);

	m_lessonListModel = new QStandardItemModel (this);
	m_lessonsListView->setModel (m_lessonListModel);

	m_wordsTable = new QTableView (m_mainSplitter);

	m_wordListModel = new QStandardItemModel (this);
	m_wordsTable->setModel (m_wordListModel);
	QStandardItem *orHeaderItem = new QStandardItem ("German");
	QStandardItem *trHeaderItem = new QStandardItem ("French");
	m_wordListModel->setHorizontalHeaderItem (OR_COL, orHeaderItem);
	m_wordListModel->setHorizontalHeaderItem (TR_COL, trHeaderItem);
	m_wordsTable->horizontalHeader ()->setSectionResizeMode (QHeaderView::Stretch);
	m_wordsTable->verticalHeader ()->hide ();

	m_mainSplitter->setStretchFactor (0, 0);
	m_mainSplitter->setStretchFactor (1, 1);
}

void MainWindow::setEventDispatcher (MainEventDispatcher * dispatcher)
{
	m_eventDispatcher = dispatcher;
	QObject::connect (m_lessonsListView, &QListView::doubleClicked, m_eventDispatcher, &MainEventDispatcher::onLessonDoubleClicked);
	QObject::connect (m_wordListModel, &QStandardItemModel::itemChanged, m_eventDispatcher, &MainEventDispatcher::onWordTableItemChanged);
	QObject::connect (m_changeFolderButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onChangeFolderButtonClicked);
}

void MainWindow::launchUserInterface ()
{
	this->show ();
}

void MainWindow::displayLessonList (QDir folder, QFileInfoList & lessonList)
{
	m_lessonListModel->clear ();
	m_wordListModel->removeRows (0, m_wordListModel->rowCount ());

	m_folderNameLabel->setFullText (folder.absolutePath ());
	
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
	m_wordListModel->removeRows (0, m_wordListModel->rowCount ());
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

	m_wordsTable->setFocus ();

	lastAsked = new QModelIndex(m_wordListModel->indexFromItem (itemEmpty));
	m_wordsTable->setCurrentIndex (*lastAsked);
	m_wordsTable->edit (*lastAsked);
}

void MainWindow::giveAnswer (QString originalWord, QString translatedWord, bool success)
{
	if (lastAsked)
	{
		QStandardItem *askedItem = m_wordListModel->item (lastAsked->row (), lastAsked->column ());
		bool askedItemWasOriginalText = lastAsked->column () == OR_COL;

		delete lastAsked;
		lastAsked = NULL;

		if (askedItemWasOriginalText)
		{ // original
			askedItem->setText (originalWord);
		}
		else
		{ // translated
			askedItem->setText (translatedWord);
		}
		if (success)
		{
			askedItem->setForeground (Qt::GlobalColor::green);
		}
		else
		{
			askedItem->setForeground (Qt::GlobalColor::red);
		}
	}
}

void MainWindow::showTrainingEnded (int correctAnswers, int totalAnswers, QList<std::tuple<QString, QString, bool, QString>>& answers)
{
	setFocus ();
	m_wordsTable->clearSelection ();
}

QDir MainWindow::openFileDialog (QDir dir)
{
	QFileDialog fileDialog (this);
	fileDialog.setDirectory (dir);
	fileDialog.setFileMode (QFileDialog::DirectoryOnly);
	fileDialog.setOption (QFileDialog::ShowDirsOnly, false);
	fileDialog.exec ();
	
	return fileDialog.directory ();
}
