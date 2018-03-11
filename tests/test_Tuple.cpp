#include "libs\catch.hpp"
#include "src\model\Tuple.h"
#include <sstream>

unsigned int parseTupleTest () 
{
	Tuple tuple;
	std::string inputString("das Kleid : le vêtement");
	std::istringstream ss(inputString);
	ss >> tuple;

	if (tuple.getOriginal () != "das Kleid")
		return 1;
	if (tuple.getTranslated () != "le vêtement")
		return 2;
	return 0;
}

unsigned int printTupleTest () 
{
	Tuple tuple;
	tuple.setOriginal ("das Kleid");
	tuple.setTranslated ("le vêtement");
	
	std::ostringstream ss;

	ss << tuple;
	if (ss.str () != "das Kleid : le vêtement")
		return 1;
	return 0;
}

TEST_CASE ("Tuple parsing and printing test", "[Tuple operator>>]") 
{
	REQUIRE (parseTupleTest () == 0);
	REQUIRE (printTupleTest () == 0);
}