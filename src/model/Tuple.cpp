#include "Tuple.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Tuple& tuple)
{
	os << tuple.m_original << " : " << tuple.m_translated;
	// write obj to stream
	return os;
}

std::istream& operator>>(std::istream& is, Tuple& tuple)
{
	static const std::regex fullTupleRegex (TUPLE_REGEX_STRING, std::regex_constants::icase);

	//STOPPED HERE

	// read obj from stream
	bool failed = true;
	std::string line;
	std::getline (is, line);
	bool valid = std::regex_match (line, fullTupleRegex);

	if (valid)
	{
		std::string::size_type pos = line.find (':');
		if (pos > 0 && line.at(pos-1) == ' ')
		{
			tuple.m_original = line.substr (0, pos - 1);
		}

		if (pos + 2 < line.length () && line.at (pos + 1) == ' ')
		{
			tuple.m_translated = line.substr (pos+2);
		}
	}

	return is;
}
