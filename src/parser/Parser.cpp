#include "Parser.h"

#include <fstream>
#include <filesystem>

/*structure of translation files :

das Kleid : le vêtement
drehen : tourner
sich über jemand lustig machen : se moquer de quelqu'un, rire aux dépend de quelqu'un*/
std::tuple<Lesson, Parser::IOStatus> Parser::parseFile (std::string filePath)
{
	std::ifstream file (filePath, std::ios::in);

	Lesson lesson;

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

	for (std::experimental::filesystem::directory_entry it : std::experimental::filesystem::directory_iterator (folderPath))
	{
		if (it.path ().extension().string() == DEFAULT_LESSON_FILE_EXTENSION)
		{
			list.push_back (it.path().filename().string ());
		}
	}

	return list;
}
