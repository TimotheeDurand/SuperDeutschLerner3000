#include "view\UI\MainEventDispatcher.h"
#include "view\UI\MainWindow.h"
#include "controller\Controller.h"
#include <QApplication>

int main(int argc, char** argv)
{
	QApplication a (argc, argv);

	Controller controller;
	if (argc > 1) controller.setFolderPath (QString(argv[1]));
	MainWindow viewer;
	controller.setViewer (&viewer);
	MainEventDispatcher dispatcher(&controller, &viewer);
	viewer.setEventDispatcher (&dispatcher);
	viewer.launchUserInterface ();
	controller.showLessons ();
	return a.exec();
}