#pragma once

#include <string>
#include <tuple>

#include "src\model\Lesson.h"

/* Class Parser:

	The parser create Lessons from files and files from Lessons
*/

class Parser 
{
public:
	enum IOStatus{ SUCCESS, CANNOT_OPEN_FILE};
	std::tuple<Lesson, IOStatus> parseFile (std::string filePath);
	IOStatus writeFile (Lesson &lesson, std::string filePath);
};