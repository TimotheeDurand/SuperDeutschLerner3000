#include "libs\catch.hpp"
#include "src\model\Tuple.h"
#include <sstream>

unsigned int parseTupleTest () 
{
	Tuple tuple;
	QString inputString = QString::fromLocal8Bit("das Kleid : le vêtement");
	QTextStream ss(&inputString);
	ss >> tuple;

	if (tuple.getOriginal () != QString::fromLocal8Bit("das Kleid"))
		return 1;
	if (tuple.getTranslated () != QString::fromLocal8Bit("le vêtement"))
		return 2;
	return 0;
}

unsigned int printTupleTest () 
{
	Tuple tuple;
	tuple.setOriginal (QString::fromLocal8Bit("das Kleid"));
	tuple.setTranslated (QString::fromLocal8Bit("le vêtement"));
	
	QString input;
	QTextStream ss(&input);

	ss << tuple;

	if (ss.readAll() != QString::fromLocal8Bit("das Kleid : le vêtement"))
		return 1;
	return 0;
}

TEST_CASE ("Tuple parsing and printing test", "[Tuple operator>>]") 
{
	REQUIRE (parseTupleTest () == 0);
	REQUIRE (printTupleTest () == 0);
}