#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>

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

	QVBoxLayout *mainLayout = new QVBoxLayout (this);
	mainLayout->setContentsMargins (0, 0, 0, 0);
	mainLayout->setSpacing (0);

	QHBoxLayout *layout = new QHBoxLayout ();
	layout->setContentsMargins (0, 0, 0, 0);
	layout->setSpacing (0);
	mainLayout->addLayout (layout);

	QHBoxLayout *downRibbonLayout = new QHBoxLayout ();
	downRibbonLayout->setContentsMargins (0, 0, 0, 0);
	downRibbonLayout->setSpacing (0);
	mainLayout->addLayout (downRibbonLayout);
	mainLayout->setStretch (0, 1);
	mainLayout->setStretch (1, 0);

	m_infoLabel = new QLabel ("Welcome !");
	m_infoLabel->setObjectName ("Info");
	downRibbonLayout->addWidget (m_infoLabel);
	m_infoScoreLabel = new QLabel ("");
	m_infoScoreLabel->setObjectName ("InfoScore");
	downRibbonLayout->addWidget (m_infoScoreLabel);
	m_infoWordsLabel = new QLabel ("");
	m_infoWordsLabel->setObjectName ("InfoWords");
	m_infoWordsLabel->setAlignment (Qt::AlignRight);
	downRibbonLayout->addWidget (m_infoWordsLabel);
	setDownRibbonColor (DEFAULT_COLOR_BG, DEFAULT_COLOR_FG);
	downRibbonLayout->setStretch (0, 1);
	downRibbonLayout->setStretch (1, 0);
	downRibbonLayout->setStretch (2, 0);

	QVBoxLayout *leftRibbonLayout = new QVBoxLayout ();
	layout->addLayout (leftRibbonLayout);
	leftRibbonLayout->setAlignment (Qt::AlignTop);

	m_changeFolderButton = new QPushButton (this);	
	m_changeFolderButton->setObjectName ("ChangeFolder");
	m_changeFolderButton->setToolTip ("Change working directory");
	leftRibbonLayout->addWidget (m_changeFolderButton);

	m_startTrainingButton = new QPushButton (this);
	m_startTrainingButton->setObjectName ("StartTraining");
	m_startTrainingButton->setToolTip ("Start training on the selected lesson");
	m_startTrainingButton->setDisabled (true);
	leftRibbonLayout->addWidget (m_startTrainingButton);

	m_stopTrainingButton = new QPushButton (this);
	m_stopTrainingButton->setObjectName ("StopTraining");
	m_stopTrainingButton->setToolTip ("Interrupt the training");
	m_stopTrainingButton->hide ();
	leftRibbonLayout->addWidget (m_stopTrainingButton);

	m_mainSplitter = new QSplitter (Qt::Horizontal, this);
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
	m_wordsTable->setSelectionMode (QAbstractItemView::NoSelection);
	m_wordsTable->setEditTriggers (QAbstractItemView::NoEditTriggers);

	m_mainSplitter->setStretchFactor (0, 0);
	m_mainSplitter->setStretchFactor (1, 1);
}

void MainWindow::setEventDispatcher (MainEventDispatcher * dispatcher)
{
	m_eventDispatcher = dispatcher;
	QObject::connect (m_lessonsListView->selectionModel(), &QItemSelectionModel::selectionChanged, m_eventDispatcher, &MainEventDispatcher::onLessonSelectionChanged);
	QObject::connect (m_lessonsListView, &QListView::doubleClicked, m_eventDispatcher, &MainEventDispatcher::onLessonDoubleClicked);
	QObject::connect (m_wordListModel, &QStandardItemModel::itemChanged, m_eventDispatcher, &MainEventDispatcher::onWordTableItemChanged);
	QObject::connect (m_changeFolderButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onChangeFolderButtonClicked);
	QObject::connect (m_startTrainingButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onStartTrainingButtonClicked);
	QObject::connect (m_stopTrainingButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onStopTrainingButtonClicked);
}

void MainWindow::launchUserInterface ()
{
	this->show ();
}

void MainWindow::displayLessonList (QDir folder, QFileInfoList & lessonList)
{
	m_lessonsListView->clearSelection ();
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
	resetTableAndInfo ();
	m_wordsTable->setSelectionMode (QAbstractItemView::SingleSelection);
	m_wordsTable->setEditTriggers (QAbstractItemView::AllEditTriggers);
	m_startTrainingButton->hide ();
	m_stopTrainingButton->show ();
	m_changeFolderButton->setDisabled (true);
	m_lessonsListView->setDisabled (true);
	setDownRibbonColor (TRAIN_COLOR_BG, TRAIN_COLOR_FG);
	askedWordCount = 0;
	correctWordsCount = 0;
	setInfo ("Training started on \'" + fileInfos.baseName () + "\' !");
	setInfoScore (0, 0);
}

void MainWindow::showTrainingEnded (int correctAnswers, int totalAnswers, QList<std::tuple<QString, QString, bool, QString>>& answers)
{
	setFocus ();
	m_wordsTable->clearSelection ();
	m_wordsTable->setSelectionMode (QAbstractItemView::NoSelection);
	m_wordsTable->setEditTriggers (QAbstractItemView::NoEditTriggers);
	m_stopTrainingButton->hide ();
	m_startTrainingButton->show ();
	m_changeFolderButton->setDisabled (false);
	m_lessonsListView->setDisabled (false);

	double score = ((double)correctAnswers / (double)totalAnswers)*20.0;
	setInfo ("Training finished ! Your grade : " + 
		QString("%1").arg(score, 1, 'f', 1) + "/20");
	setDownRibbonColor (FINISHED_COLOR_BG, FINISHED_COLOR_FG);
}

void MainWindow::askWord (QString word, bool original)
{
	askedWordCount++;
	setInfoWord ("Total: " + QString::number (askedWordCount) + "/" + QString::number (currentWordCount));
	
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
		lastAsked = nullptr;

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
			correctWordsCount++;
			askedItem->setForeground (Qt::GlobalColor::green);
		}
		else
		{
			askedItem->setForeground (Qt::GlobalColor::red);
		}
		askedItem->setEditable (false);
	}

	setInfoScore (correctWordsCount, askedWordCount-correctWordsCount);
}

void MainWindow::showFullLesson (QVector<std::pair<QString, QString>> tuples)
{
	resetTableAndInfo ();
	m_wordsTable->setSelectionMode (QAbstractItemView::NoSelection);
	for(auto tuple : tuples)
	{ 
		QStandardItem *itemOri = new QStandardItem (tuple.first);
		QStandardItem *itemTr = new QStandardItem (tuple.second);
		m_wordListModel->appendRow ({ itemOri, itemTr });
	}
	currentWordCount = tuples.size ();
	QString strInfo = QString::number(tuples.size ()) + " words";
	setInfoWord(strInfo);
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

void MainWindow::setInfo (const QString &info)
{
	m_infoLabel->setText (info);
}

void MainWindow::setInfoWord (const QString &infoWords)
{
	m_infoWordsLabel->setText (infoWords);
}

void MainWindow::setInfoScore (const QString & infoScore)
{
	m_infoScoreLabel->setText (infoScore);
}

void MainWindow::setInfoScore (int correct, int incorrect)
{
	QString totalStr = "Correct: " + QString::number (correct);
	totalStr += "    ";
	totalStr += "Errors: " + QString::number (incorrect);
	m_infoScoreLabel->setText (totalStr);
}

void MainWindow::setDownRibbonColor (const QColor & colorBG, const QColor & colorFG)
{
	QString stylesheet = "";
	stylesheet += "QLabel {background-color: ";
	stylesheet += colorBG.name ();
	stylesheet += "; color:";
	stylesheet += colorFG.name ();
	stylesheet += "}";
	m_infoWordsLabel->setStyleSheet (stylesheet);
	m_infoLabel->setStyleSheet (stylesheet);
	m_infoScoreLabel->setStyleSheet (stylesheet);
}

QStandardItem* MainWindow::getSelectedLesson ()
{
	QStandardItem* item = nullptr;
	if (!m_lessonsListView->selectionModel ()->selectedIndexes ().isEmpty ())
	{
		QModelIndex idx = m_lessonsListView->selectionModel ()->selectedIndexes ().first ();
		item = m_lessonListModel->item (idx.row ());
	}
	return item;
}

void MainWindow::resetTableAndInfo ()
{
	setDownRibbonColor (DEFAULT_COLOR_BG, DEFAULT_COLOR_FG);
	setInfoScore ("");
	setInfoWord ("");
	setInfo ("");
	m_wordListModel->removeRows (0, m_wordListModel->rowCount ());
	m_wordsTable->clearSelection ();
	if (lastAsked)
	{
		delete lastAsked;
		lastAsked = nullptr;
	}
}
