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
	void onLessonDoubleClicked (const QModelIndex &index);

private:
	MainWindow * m_mainWindow;
};