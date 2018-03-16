#include "MainEventDispatcher.h"

#include <QDebug>

MainEventDispatcher::MainEventDispatcher (Controller* controller, GenericViewer* viewer)
	: GenericEventDispatcher (controller, viewer)
{
	m_mainWindow = dynamic_cast<MainWindow*>(viewer);
}

void MainEventDispatcher::onLessonDoubleClicked (const QModelIndex &index)
{
	QStandardItem *item = m_mainWindow->getLessonModel ()->item (index.row ());
	QString fileName = item->text ();
	if (!fileName.isEmpty ())
		m_controller->startTraining (fileName);
}
