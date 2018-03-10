#pragma once

#define DEFAULT_LESSON_FILE_EXTENSION ".les"

#include <string>
#include <tuple>
#include <list>

#include "src\model\Lesson.h"

/* Class Parser:

	The parser create Lessons from files and files from Lessons
*/

class Parser 
{
public:
	enum IOStatus{ SUCCESS, CANNOT_OPEN_FILE};
	std::tuple<Lesson, Parser::IOStatus> parseFile (std::string filePath);
	IOStatus writeFile (Lesson &lesson, std::string filePath);
	std::list<std::string> listLessonsInFolder (std::string folderPath);
};