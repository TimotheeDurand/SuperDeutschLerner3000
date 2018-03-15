#include "libs\catch.hpp"
#include "src\model\Tuple.h"
#include <sstream>

unsigned int parseTupleTest () 
{
	Tuple tuple;
	QString inputString = QString::fromUtf8("das Kleid : le vêtement");
	QTextStream ss(&inputString);
	ss >> tuple;

	if (tuple.getOriginal () != QString::fromUtf8("das Kleid"))
		return 1;
	if (tuple.getTranslated () != QString::fromUtf8("le vêtement"))
		return 2;
	return 0;
}

unsigned int printTupleTest () 
{
	Tuple tuple;
	tuple.setOriginal (QString::fromUtf8("das Kleid"));
	tuple.setTranslated (QString::fromUtf8("le vêtement"));
	
	QString input;
	QTextStream ss(&input);

	ss << tuple;

	if (ss.readAll() != QString::fromUtf8("das Kleid : le vêtement"))
		return 1;
	return 0;
}

TEST_CASE ("Tuple parsing and printing test", "[Tuple operator>>]") 
{
	REQUIRE (parseTupleTest () == 0);
	REQUIRE (printTupleTest () == 0);
}