#include "Parser.h"

#include <fstream>
#include <filesystem>

// filesystem is not implemented as default in VS2017 as of version 15.5, this will change later
// to std::filesystem.
using namespace std::experimental::filesystem;

std::tuple<Lesson, Parser::IOStatus> Parser::parseFile (std::string filePath)
{
	std::ifstream file (filePath, std::ios::in);

	Lesson lesson;

	// add utf8 support WIP
	//std::locale utf8_locale (std::locale (), new std::codecvt_utf8<wchar_t>);
	//file.imbue (utf8_locale);

	if (file)
	{
		file >> lesson;
	}
	else return { lesson, CANNOT_OPEN_FILE };

	return { lesson, SUCCESS };
}

Parser::IOStatus Parser::writeFile (Lesson & lesson, std::string filePath)
{
	std::ofstream file (filePath, std::ios::out);

	if (file)
	{
		file << lesson;
	}
	else return CANNOT_OPEN_FILE;

	return SUCCESS;
}

std::list<std::string> Parser::listLessonsInFolder (std::string folderPath)
{
	std::list<std::string> list;

	for (directory_entry it : directory_iterator (folderPath))
	{
		if (it.path ().extension().string() == DEFAULT_LESSON_FILE_EXTENSION)
		{
			list.push_back (it.path().filename().string ());
		}
	}

	return list;
}
