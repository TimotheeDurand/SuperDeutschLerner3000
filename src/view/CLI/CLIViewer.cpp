#include "CLIViewer.h"

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

CLIViewer::CLIViewer () : cout(stdout, QIODevice::WriteOnly), cin (stdin, QIODevice::ReadOnly)
{
}

void CLIViewer::launchUserInterface ()
{
	cout << "SuperDeutschLerner3000 started. For a command list type \"help\"" << endl;

	do cout << endl << "SDL3k> " << flush; while (listenKeyBoardInput ());

	cout << "bye" << endl;
}

void CLIViewer::displayLessonList (QDir folder, QFileInfoList& lessonList)
{
	cout << "displaying lessons in: " << folder.path() << endl << endl;
	for (auto fileInfo : lessonList)
	{
		cout << fileInfo.fileName() << endl;
	}
}

void CLIViewer::showFullLesson (QVector<std::pair<QString, QString>> tuples)
{
	//TODO
}

void CLIViewer::showCommandList ()
{
	QList<QPair<QString, QString>> cmdHelps;
	cmdHelps.push_back ({ "pwd", "show the current working directory" });
	cmdHelps.push_back ({ "cd [dir]", "change current working directory to [dir]" });
	cmdHelps.push_back ({ "help (h)", "display command list" });
	cmdHelps.push_back ({ "lessons (ls)", "show the lessons in the current directory" });
	cmdHelps.push_back ({ "train (t) [file.les]", "start a training session on the [file.les]" });
	cmdHelps.push_back ({ "exit", "exit SDL3k" });
	
	for (auto pair : cmdHelps)
	{
		cout.setFieldWidth (25);
		cout << left << pair.first;
		cout.setFieldWidth (0);
		cout << pair.second;
		cout << endl;
	}
}

void CLIViewer::showWorkingDirectory (QDir dir)
{
	cout << dir.path() << endl;
}

void CLIViewer::showUnknownCommand (QString command)
{
	cout << "Unknown command: \'" << command << '\'' << endl;
}

void CLIViewer::showPathMissing ()
{
	cout << "Please provide a path" << endl;
}

void CLIViewer::showFileMissing ()
{
	cout << "Please provide a lesson file name" << endl;
}

void CLIViewer::showFileError (QFileInfo fileInfo)
{
	cout << "Error" << " : could not open file \'" << fileInfo.fileName() << '\''<< endl;
}

void CLIViewer::showTrainingStarted (QFileInfo fileInfo)
{
	cout << "TRAINING STARTED" << endl;
	cout << "To stop training, type \"STOP\"" << endl;
	cout << "lesson selected : " << fileInfo.fileName() << endl;
	cout << "GOOD LUCK" << endl << endl;
}

void CLIViewer::showTrainingEnded (
	int correctAnswers,
	int totalAnswers,
	QList<std::tuple<QString, QString, bool, QString>>& answers)
{
	for (auto answer : answers)
	{
		auto[stro, strt, correct, given] = answer;
		
		cout.setFieldWidth (40);
		if (correct)
		{
			cout << left << "correct" << flush;
		}
		else
		{
			cout << left << "INCORRECT" << flush;
		}
		cout.setFieldWidth (0);
		utf8Print (stro);
		cout << " : " << flush;
		utf8Print (strt);
		cout << endl;

		if (!correct)
		{
			cout << "You said: " << flush;
			utf8Print (given);
			cout << endl;
		}
	}
	cout << endl;

	cout << "TRAINING SESSION OVER" << endl;
	cout << "Correct answers:";
	cout.setFieldWidth (4);
	cout << correctAnswers;
	cout.setFieldWidth (0);
	cout << endl;
	cout << "Errors: ";
	cout.setFieldWidth (9 + 4);
	cout << (totalAnswers - correctAnswers);
	cout.setFieldWidth (0);
	cout << endl;
}


void CLIViewer::giveAnswer (QString originalWord, QString translatedWord, bool success)
{
	utf8Print (originalWord);
	cout << " : " << flush;
	utf8Print (translatedWord);
	if (success)
	{
		cout << " CORRECT" << endl;
	}
	else
	{
		cout << " INCORRECT" << endl;
	}
	cout << endl;
}

void CLIViewer::askWord (QString word, bool original)
{
	cout << "What's the meaning of : \"" << flush;
	utf8Print (word);
	cout << '\"' << endl;
}

bool CLIViewer::listenKeyBoardInput ()
{
	QString userInput;
	userInput = readLine ();
	cout << endl;
	return eventDispatcher->handleUserInput (userInput);
}

void CLIViewer::utf8Print (QString string)
{
#ifdef Q_OS_WIN32
	WriteConsoleW (GetStdHandle (STD_OUTPUT_HANDLE),
		string.utf16 (), string.size (), NULL, NULL);
#else
	cout << string;
#endif
}

QString CLIViewer::readLine ()
{
#ifdef Q_OS_WIN32
	const int bufsize = 512;
	wchar_t buf[bufsize];
	DWORD read;
	QString res;
	do {
		ReadConsoleW (GetStdHandle (STD_INPUT_HANDLE),
			buf, bufsize, &read, NULL);
		res += QString::fromWCharArray (buf, read);
	} while (read > 0 && res[res.length () - 1] != '\n');
	// could just do res.truncate(res.length() - 2), but better be safe
	while (res.length () > 0
		&& (res[res.length () - 1] == '\r' || res[res.length () - 1] == '\n'))
		res.truncate (res.length () - 1);
	return res;
#else
	return cin.readLine ();
#endif
}

