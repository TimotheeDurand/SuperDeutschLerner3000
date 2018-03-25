#pragma once

#define DEFAULT_LESSON_FILE_EXTENSION ".les"

#include <tuple>
#include <QDir>
#include <QFileInfo>

#include "src\model\Lesson.h"

/* Class Parser:

	The parser create Lessons from files and files from Lessons
*/

class Parser 
{
public:
	enum IOStatus{ SUCCESS, CANNOT_OPEN_FILE};
	std::tuple<Lesson, Parser::IOStatus> parseFile (const QFileInfo &fileInfos);
	IOStatus writeFile (Lesson &lesson, const QFileInfo &fileInfos);
	QFileInfoList listLessonsInFolder (const QDir &dir);
	QString MoveFileToTrash (const QFileInfo &fileInfo);

private:
	QString MoveToTrashImpl (const QFileInfo & fileinfo);
};