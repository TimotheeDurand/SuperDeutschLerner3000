#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
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

	m_createLessonButton = new QPushButton (this);
	m_createLessonButton->setObjectName ("CreateLesson");
	m_createLessonButton->setToolTip ("Create a new lesson");
	leftRibbonLayout->addWidget (m_createLessonButton);

	m_deleteLessonButton = new QPushButton (this);
	m_deleteLessonButton->setObjectName ("DeleteLesson");
	m_deleteLessonButton->setToolTip ("Delete selected lesson");
	m_deleteLessonButton->setDisabled (true);
	leftRibbonLayout->addWidget (m_deleteLessonButton);

	m_editLessonButton = new QPushButton (this);
	m_editLessonButton->setObjectName ("EditLesson");
	m_editLessonButton->setToolTip ("Edit selected lesson");
	m_editLessonButton->setDisabled (true);
	leftRibbonLayout->addWidget (m_editLessonButton);

	m_closeLessonButton = new QPushButton (this);
	m_closeLessonButton->setObjectName ("CloseLesson");
	m_closeLessonButton->setToolTip ("Stop editing");
	m_closeLessonButton->hide ();
	leftRibbonLayout->addWidget (m_closeLessonButton);

	m_saveLessonButton = new QPushButton (this);
	m_saveLessonButton->setObjectName ("SaveLesson");
	m_saveLessonButton->setToolTip ("Save lesson");
	m_saveLessonButton->hide ();
	leftRibbonLayout->addWidget (m_saveLessonButton);

	m_deleteRowButton = new QPushButton (this);
	m_deleteRowButton->setObjectName ("DeleteRow");
	m_deleteRowButton->setToolTip ("Delete the selected row");
	m_deleteRowButton->hide ();
	leftRibbonLayout->addWidget (m_deleteRowButton);

	m_mainSplitter = new QSplitter (Qt::Horizontal, this);
	layout->addWidget (m_mainSplitter);

	QWidget *folderLayoutContainer = new QWidget (m_mainSplitter);
	QVBoxLayout *folderDisplayLayout = new QVBoxLayout (folderLayoutContainer);
	folderDisplayLayout->setContentsMargins (0, 0, 0, 0);
	
	m_folderNameLabel = new CompressibleLabel (m_mainSplitter);
	m_folderNameLabel->setObjectName ("DirLabel");
	folderDisplayLayout->addWidget (m_folderNameLabel);

	m_lessonDelegate = new LessonDelegate (this);
	
	m_lessonsListView = new QListView (m_mainSplitter);
	m_lessonsListView->setEditTriggers (QAbstractItemView::DoubleClicked);
	m_lessonsListView->setItemDelegate (m_lessonDelegate);
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
	QObject::connect (m_lessonsListView, &QListView::clicked, m_eventDispatcher, &MainEventDispatcher::onLessonClicked);
	QObject::connect (m_wordListModel, &QStandardItemModel::itemChanged, m_eventDispatcher, &MainEventDispatcher::onWordTableItemChanged);
	QObject::connect (m_lessonDelegate, &LessonDelegate::lessonNameChanged, m_eventDispatcher, &MainEventDispatcher::onLessonNameChanged);
	QObject::connect (m_changeFolderButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onChangeFolderButtonClicked);
	QObject::connect (m_startTrainingButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onStartTrainingButtonClicked);
	QObject::connect (m_stopTrainingButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onStopTrainingButtonClicked);
	QObject::connect (m_createLessonButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onButtonCreateLessonClicked);
	QObject::connect (m_deleteLessonButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onButtonDeleteLessonClicked);
	QObject::connect (m_editLessonButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onButtonStartEditingClicked);
	QObject::connect (m_closeLessonButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onButtonCloseEditingClicked);
	QObject::connect (m_saveLessonButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onButtonSaveLessonClicked);
	QObject::connect (m_deleteRowButton, &QPushButton::clicked, m_eventDispatcher, &MainEventDispatcher::onButtonDeleteRowClicked);
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
		m_lessonListModel->appendRow (item);
	}
}

void MainWindow::refreshLessonList (QDir folder, QFileInfoList & lessonList)
{
	m_lessonsListView->clearSelection ();
	m_lessonListModel->clear ();
	m_wordListModel->removeRows (0, m_wordListModel->rowCount ());

	m_folderNameLabel->setFullText (folder.absolutePath ());

	for (auto lesson : lessonList)
	{
		QStandardItem *item = new QStandardItem (lesson.fileName ());
		m_lessonListModel->appendRow (item);
	}
}

void MainWindow::showFileError (QFileInfo fileInfos, FileError error)
{
	QModelIndexList list;
	QStandardItem *item;
	switch (error)
	{
	case DIR_UNACCESSIBLE:
		QMessageBox::warning (this, "Directory error", fileInfos.absolutePath () + " is unaccessible.");
		break;
	case CANNOT_OPEN:
		QMessageBox::warning (this, "File opening error", "Could not open file \'" + fileInfos.fileName () + "\'.");
		break;
	case CANNOT_RENAME:
		QMessageBox::warning (this, "Renaming error", "Could not rename file \'" + fileInfos.baseName () + "\'.");
		list = m_lessonListModel->match (m_lessonListModel->index (0, 0), Qt::DisplayRole, this->getNewLessonName());
		if (!list.empty ())
		{
			item = m_lessonListModel->item(list.first ().row(), list.first().column());
			item->setText (getLastLessonName ());
		}
		break;
	case CANNOT_CREATE:
		QMessageBox::warning (this, "File error", "Could not create a new file.");
		break;
	case CANNOT_DELETE:
		QMessageBox::warning (this, "File error", "Could not delete file \'" + fileInfos.baseName () + "\'.");
		break;
	case CANNOT_WRITE:
		QMessageBox::warning (this, "File error", "Could not write file \'" + fileInfos.baseName () + "\'.");
	}
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
	m_editLessonButton->setDisabled (true);
	m_deleteLessonButton->setDisabled (true);
	m_createLessonButton->setDisabled (true);
	setDownRibbonColor (TRAIN_COLOR_BG, TRAIN_COLOR_FG);
	m_askedWordCount = 0;
	m_correctWordsCount = 0;
	setInfo ("Training started on \'" + fileInfos.fileName () + "\' !");
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
	m_editLessonButton->setDisabled (false);
	m_deleteLessonButton->setDisabled (false);
	m_createLessonButton->setDisabled (false);

	double score = ((double)correctAnswers / (double)totalAnswers)*20.0;
	setInfo ("Training finished ! Your grade : " + 
		QString("%1").arg(score, 1, 'f', 1) + "/20");
	setDownRibbonColor (FINISHED_COLOR_BG, FINISHED_COLOR_FG);
}

void MainWindow::askWord (QString word, bool original)
{
	m_askedWordCount++;
	setInfoWord ("Total: " + QString::number (m_askedWordCount) + "/" + QString::number (m_currentWordCount));
	
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
			m_correctWordsCount++;
			askedItem->setForeground (Qt::GlobalColor::green);
		}
		else
		{
			askedItem->setForeground (Qt::GlobalColor::red);
		}
		askedItem->setEditable (false);
	}

	setInfoScore (m_correctWordsCount, m_askedWordCount-m_correctWordsCount);
}

void MainWindow::showFullLesson (QFileInfo lessonFile, QVector<std::pair<QString, QString>> tuples)
{
	static bool preventMultiple = false;
	if (!preventMultiple)
	{
		preventMultiple = true;
		resetTableAndInfo ();
		QModelIndexList idxs = m_lessonListModel->match (m_lessonsListView->indexAt (QPoint (0, 0)), Qt::EditRole, lessonFile.fileName ());
		if (!idxs.empty ())
		{
			m_lessonsListView->setCurrentIndex (idxs.first ());
		}
		m_wordsTable->setSelectionMode (QAbstractItemView::NoSelection);
		for (auto tuple : tuples)
		{
			QStandardItem *itemOri = new QStandardItem (tuple.first);
			QStandardItem *itemTr = new QStandardItem (tuple.second);
			m_wordListModel->appendRow ({ itemOri, itemTr });
		}
		m_currentWordCount = tuples.size ();
		setInfo ("file: \'" + lessonFile.absoluteFilePath () + "\'");
		QString strInfo = QString::number (tuples.size ()) + " words";
		setInfoWord (strInfo);
		preventMultiple = false;
	}
}

void MainWindow::showEditingStarted (QFileInfo fileInfos, QVector<std::pair<QString, QString>>& tuples)
{
	resetTableAndInfo ();
	m_modified = false;
	setDownRibbonColor (EDITING_COLOR_BG, EDITING_COLOR_FG);
	setInfo ("You are now editing \'" + fileInfos.fileName () + "\'");
	m_wordsTable->setSelectionMode (QAbstractItemView::SingleSelection);
	m_wordsTable->setEditTriggers (QAbstractItemView::AllEditTriggers);
	m_startTrainingButton->setDisabled (true);
	m_changeFolderButton->setDisabled (true);
	m_lessonsListView->setDisabled (true);
	m_deleteLessonButton->setDisabled (true);
	m_createLessonButton->setDisabled (true);
	m_editLessonButton->hide ();
	m_closeLessonButton->show ();
	m_saveLessonButton->show ();
	m_deleteRowButton->show ();
	for (auto tuple : tuples)
	{
		QStandardItem *itemOri = new QStandardItem (tuple.first);
		QStandardItem *itemTr = new QStandardItem (tuple.second);
		m_wordListModel->appendRow ({ itemOri, itemTr });
	}
	m_wordListModel->appendRow ({ new QStandardItem (), new QStandardItem () });
	QModelIndex newItemIdx = m_wordListModel->index (m_wordListModel->rowCount () - 1, OR_COL);
	m_wordsTable->setCurrentIndex (newItemIdx);
	m_wordsTable->edit (newItemIdx);
	m_currentWordCount = tuples.size ();
	QString strInfo = QString::number (tuples.size ()) + " words";
	setInfoWord (strInfo);
}

void MainWindow::showTupleInvalid (QString old_originalWord, QString old_translatedWord, int idx)
{
	bool edited = idx < m_wordListModel->rowCount () - 1;
	if (edited)
	{
		setInfo ("ERROR: Invalid word, cannot edit");
	}
	else
	{
		setInfo ("ERROR: Invalid word, cannot add");
	}
	QString strInfo = QString::number (m_wordListModel->rowCount ()) + " words";
	QStandardItem* itemOr = m_wordListModel->item (idx, OR_COL);
	QStandardItem* itemTr = m_wordListModel->item (idx, TR_COL);
	m_dontListenEdit = true;
	itemOr->setText (old_originalWord);
	itemTr->setText (old_translatedWord);
	m_dontListenEdit = false;
}

void MainWindow::showTupleAdded (QString originalWord, QString translatedWord, int index)
{
	bool edited = index < m_wordListModel->rowCount () - 1;
	if (edited)
	{
		setInfo ("Word edited : \'" + originalWord + " : " + translatedWord + "\'");
	}
	else
	{
		setInfo ("Word added : \'" + originalWord + " : " + translatedWord + "\'");

		m_wordListModel->appendRow ({ new QStandardItem (), new QStandardItem () });
		QModelIndex newItemIdx = m_wordListModel->index (m_wordListModel->rowCount () - 1, OR_COL);
		m_wordsTable->setCurrentIndex (newItemIdx);
		m_wordsTable->edit (newItemIdx);
	}
	m_modified = true;
	QString strInfo = QString::number (m_wordListModel->rowCount ()-1) + " words";
	setInfoWord (strInfo);
}

void MainWindow::showRowDeleted (QString old_originalWord, QString old_translatedWord, int index)
{
	setInfo ("Word deleted : \'" + old_originalWord + " : " + old_translatedWord + "\'");
	m_wordListModel->removeRow (index);
	m_modified = true;
	QString strInfo = QString::number (m_wordListModel->rowCount ()-1) + " words";
	setInfoWord (strInfo);
}

void MainWindow::showLessonSaved (QFileInfo lessonFile)
{
	setInfo ("\'" + lessonFile.fileName () + "\' successfully saved");
	m_modified = false;
}

void MainWindow::showLessonClosed (QFileInfo lessonFile)
{
	setFocus ();
	m_wordsTable->clearSelection ();
	m_wordsTable->setSelectionMode (QAbstractItemView::NoSelection);
	m_wordsTable->setEditTriggers (QAbstractItemView::NoEditTriggers);
	m_startTrainingButton->setDisabled (false);
	m_changeFolderButton->setDisabled (false);
	m_lessonsListView->setDisabled (false);
	m_deleteLessonButton->setDisabled (false);
	m_createLessonButton->setDisabled (false);
	m_saveLessonButton->hide ();
	m_closeLessonButton->hide ();
	m_deleteRowButton->hide ();
	m_editLessonButton->show ();
}

void MainWindow::showFileCreated (QFileInfo lessonFile)
{
	setInfo ("\'" + lessonFile.fileName() + "\' created");
}

void MainWindow::showFileDeleted (QFileInfo lessonFile)
{
	setInfo ("\'" + lessonFile.fileName() + "\' moved to the recycle bin");
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

void MainWindow::disableLessonInteractionButtons (bool disable)
{
	m_startTrainingButton->setDisabled (disable);
	m_deleteLessonButton->setDisabled (disable);
	m_editLessonButton->setDisabled (disable);
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

QMessageBox::StandardButton MainWindow::shouldWeSave ()
{
	if (m_modified)
	{
		QMessageBox msg;
		msg.setWindowTitle ("Lesson modified");
		msg.setText ("Save before closing ?");
		msg.setStandardButtons (QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		return (QMessageBox::StandardButton)msg.exec ();
	}
	return QMessageBox::StandardButton::No;
}

int MainWindow::getSelectedRow ()
{
	if (!m_wordsTable->selectionModel ()->selectedIndexes ().isEmpty ())
	{
		QModelIndex idx = m_wordsTable->selectionModel ()->selectedIndexes ().first ();
		return idx.row ();
	}
	return NO_ROW;
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
