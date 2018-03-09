#include "Parser.h"

#include <fstream>

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
