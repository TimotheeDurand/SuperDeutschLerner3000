#include "catch.hpp"
#include "src\model\Lesson.h"
#include <sstream>

unsigned int parseLessonTest () 
{
	Lesson lesson;
	std::string inputString("das Kleid : le vêtement\ndie Katze :fail le chat\nlernen : apprendre");
	std::istringstream ss(inputString);
	ss >> lesson;
	Tuple t = lesson.getDictionnary ().at (0);
	Tuple t3 = lesson.getDictionnary ().at (1);
	if (t.getOriginal () == "das Kleid"
		&& t.getTranslated () == "le vêtement"
		&& t3.getOriginal () == "lernen"
		&& t3.getTranslated () == "apprendre")
		return 0;
	return 1;
}

unsigned int printLessonTest () 
{
	Tuple tuple;
	tuple.setOriginal ("das Kleid");
	tuple.setTranslated ("le vêtement");

	Tuple tuple2;
	tuple2.setOriginal ("lernen");
	tuple2.setTranslated ("apprendre");

	DictionnaryType dict;
	dict.push_back (tuple);
	dict.push_back (tuple2);

	Lesson lesson (dict);
	std::stringstream ss;
	ss << "das Kleid : le vêtement" << std::endl;
	ss << "lernen : apprendre" << std::endl;

	std::stringstream ss2;
	ss2 << lesson;

	if (ss.str () != ss2.str ())
		return 1;

	return 0;
}

TEST_CASE ("Lesson parsing and printing test", "[Tuple operator>>]") 
{
	REQUIRE (parseLessonTest () == 0);
	REQUIRE (printLessonTest () == 0);
}