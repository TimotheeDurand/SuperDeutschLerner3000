#include "libs\catch.hpp"
#include "src\model\Lesson.h"
#include <sstream>

unsigned int parseLessonTest () 
{
	Lesson lesson;
	QString inputString = QString::fromLocal8Bit("das Kleid : le vêtement\ndie Katze :fail le chat\nlernen : apprendre");
	QTextStream ss(&inputString);
	ss >> lesson;
	Tuple t = lesson.getDictionnary ().at (0);
	Tuple t3 = lesson.getDictionnary ().at (1);
	if (t.getOriginal () == QString::fromLocal8Bit("das Kleid")
		&& t.getTranslated () == QString::fromLocal8Bit("le vêtement")
		&& t3.getOriginal () == QString::fromLocal8Bit("lernen")
		&& t3.getTranslated () == QString::fromLocal8Bit("apprendre"))
		return 0;
	return 1;
}

unsigned int printLessonTest () 
{
	Tuple tuple;
	tuple.setOriginal (QString::fromLocal8Bit("das Kleid"));
	tuple.setTranslated (QString::fromLocal8Bit("le vêtement"));

	Tuple tuple2;
	tuple2.setOriginal (QString::fromLocal8Bit("lernen"));
	tuple2.setTranslated (QString::fromLocal8Bit("apprendre"));

	DictionnaryType dict;
	dict.push_back (tuple);
	dict.push_back (tuple2);

	Lesson lesson (dict);
	QString input;
	QTextStream ss (&input);
	ss << QString::fromLocal8Bit("das Kleid : le vêtement") << endl;
	ss << QString::fromLocal8Bit("lernen : apprendre") << endl;

	QString input2;
	QTextStream ss2(&input2);
	ss2 << lesson;

	if (ss.readAll() != ss2.readAll ())
		return 1;

	return 0;
}

TEST_CASE ("Lesson parsing and printing test", "[Tuple operator>>]") 
{
	REQUIRE (parseLessonTest () == 0);
	REQUIRE (printLessonTest () == 0);
}