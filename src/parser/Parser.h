#pragma once

#include <string>

#include "src\model\Lesson.h"

/* Class Parser:

	The parser create Lessons from files and files from Lessons
*/

class Parser 
{
public:
	enum WriteStatus{ SUCESS };
	Lesson parseFile (std::string filePath);
	WriteStatus writeFile (Lesson &lesson);
};