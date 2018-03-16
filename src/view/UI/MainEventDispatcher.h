#pragma once

#include "src\view\GenericEventDispatcher.h"
#include "MainWindow.h"

class MainWindow;

class MainEventDispatcher : public GenericEventDispatcher
{
public:
	MainEventDispatcher (Controller* controller, GenericViewer* viewer);

public slots:
	

private:
	MainWindow * mainWindow;
};