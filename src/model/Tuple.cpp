#include "Tuple.h"

std::ostream& operator<<(std::ostream& os, const Tuple& tuple)
{
	os << tuple.m_original << " : " << tuple.m_translated;
	// write obj to stream
	return os;
}

std::istream& operator>>(std::istream& is, Tuple& tuple)
{
	static const std::regex fullTupleRegex (TUPLE_REGEX_STRING);

	//STOPPED HERE

	// read obj from stream
	bool failed = true;
	char line[256];
	is.getline (line, 256);

	if (failed)
		is.setstate (std::ios::failbit);
	return is;
}
