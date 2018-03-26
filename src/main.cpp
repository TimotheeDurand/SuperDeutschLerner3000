#include "view\UI\MainEventDispatcher.h"
#include "view\UI\MainWindow.h"
#include "controller\Controller.h"
#include <QApplication>
#include <QFileInfo>
#include <QSettings>

#define COMPANY_NAME "TimotheeDurandDev"
#define SOFTWARE_NAME "SuperDeutschLerner3000"
#define REGKEY_DIRECTORY "WorkingDirectory"

int main(int argc, char** argv)
{
	QApplication a (argc, argv);
	Q_INIT_RESOURCE (resources);

	// registery interface
	QSettings settings (COMPANY_NAME, SOFTWARE_NAME);

	Controller controller;
	MainWindow viewer;
	controller.setViewer (&viewer);
	MainEventDispatcher dispatcher(&controller, &viewer);
	viewer.setEventDispatcher (&dispatcher);
	viewer.launchUserInterface ();

	if (argc > 1)	// if lesson name given as parameter -> we open it (lesson file double clicked)
	{
		QFileInfo fileInfo = QString (argv[1]);
		controller.setFolderPath (fileInfo.absolutePath ());
		controller.showLessons ();
		controller.showLesson (fileInfo);
	}
	else			// if no parameter given, we try to retrieve the last directory from the registry
	{
		if (settings.contains (REGKEY_DIRECTORY))
		{
			QString path = settings.value (REGKEY_DIRECTORY).toString ();
			QDir dir (path);
			if (dir.exists ())
			{
				controller.setFolderPath (path);
			}
		}
		controller.showLessons ();
	}

	int ret = a.exec ();

	// after app closure, save last working directory in the register
	QDir workingDirectory = controller.getFolderPath ();

	if (workingDirectory.exists ())
	{
		settings.setValue (REGKEY_DIRECTORY, workingDirectory.absolutePath ());
	}

	return ret;
}