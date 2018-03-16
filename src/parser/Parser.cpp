#include "Parser.h"

std::tuple<Lesson, Parser::IOStatus> Parser::parseFile (const QFileInfo& fileInfo)
{
	QFile file (fileInfo.filePath ());
	Lesson lesson;

	if (file.open (QIODevice::ReadOnly))
	{
		QTextStream in (&file);
		in.setCodec ("UTF-8");
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
