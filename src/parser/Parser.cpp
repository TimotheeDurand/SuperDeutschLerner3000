#include "Parser.h"

#include <fstream>
#include <filesystem>

// filesystem is not implemented as default in VS2017 as of version 15.5, this will change later
// to std::filesystem.
using namespace std::experimental::filesystem;

std::tuple<Lesson, Parser::IOStatus> Parser::parseFile (const QFileInfo& fileInfo)
{
	QFile file (fileInfo.filePath ());
	Lesson lesson;

	if (file.open (QIODevice::ReadOnly))
	{
		QTextStream in (&file);
		in >> lesson;
		file.close ();
	}
	else return { lesson, CANNOT_OPEN_FILE };

	return { lesson, SUCCESS };
}

Parser::IOStatus Parser::writeFile (Lesson & lesson, const QFileInfo& fileInfo)
{
	QFile file (fileInfo.filePath ());
	
	if (file.open (QIODevice::WriteOnly))
	{
		QTextStream out(&file);
		out << lesson;
		file.close ();
	}
	else return CANNOT_OPEN_FILE;

	return SUCCESS;
}

QFileInfoList Parser::listLessonsInFolder (const QDir& dir)
{
	return dir.entryInfoList ({ QString ("*") + QString (DEFAULT_LESSON_FILE_EXTENSION) });;
}
