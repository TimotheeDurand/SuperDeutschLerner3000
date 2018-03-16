#include "MainEventDispatcher.h"

MainEventDispatcher::MainEventDispatcher (Controller* controller, GenericViewer* viewer)
	: GenericEventDispatcher (controller, viewer)
{
	mainWindow = dynamic_cast<MainWindow*>(viewer);
}
