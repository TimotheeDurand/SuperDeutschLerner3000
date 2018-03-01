#include "Lesson.h"

Lesson::Lesson ()
{

}

std::ostream& operator<<(std::ostream& os, const Lesson& lesson)
{
	for (auto it : lesson.m_dictionnary)
	{
		os << it;
	}
	// write obj to stream
	return os;
}

std::istream& operator>>(std::istream& is, Lesson& lesson)
{
	// read obj from stream
	bool failed = true;
	if (failed)
		is.setstate (std::ios::failbit);
	return is;
}
