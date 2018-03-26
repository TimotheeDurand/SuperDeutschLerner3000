#include "view\UI\MainEventDispatcher.h"
#include "view\UI\MainWindow.h"
#include "controller\Controller.h"
#include <QApplication>
#include <QFileInfo>

int main(int argc, char** argv)
{
	QApplication a (argc, argv);
	Q_INIT_RESOURCE (resources);

	Controller controller;
	MainWindow viewer;
	controller.setViewer (&viewer);
	MainEventDispatcher dispatcher(&controller, &viewer);
	viewer.setEventDispatcher (&dispatcher);
	viewer.launchUserInterface ();
	if (argc > 1)
	{
		QFileInfo fileInfo = QString (argv[1]);
		controller.setFolderPath (fileInfo.absolutePath ());
		controller.showLessons ();
		controller.showLesson (fileInfo);
	}
	else
	{
		controller.showLessons ();
	}
	return a.exec();
}