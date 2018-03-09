#include "Lesson.h"

Lesson::Lesson ()
{

}

std::ostream& operator<<(std::ostream& os, const Lesson& lesson)
{
	for (auto it : lesson.m_dictionnary)
	{
		os << it << std::endl;
	}

	return os;
}

std::istream& operator>>(std::istream& is, Lesson& lesson)
{
	// retrieving the number of lines == the number of tuples in our stream
	std::ptrdiff_t count = std::count (std::istreambuf_iterator<char> (is),
		std::istreambuf_iterator<char> (), '\n');
	
	lesson.m_dictionnary.reserve (count+1);

	is.seekg (0, std::ios::beg);

	//parsing the stream
	while (is.peek() != EOF)
	{
		Tuple t;
		is >> t;
		if(t.isValid())
			lesson.m_dictionnary.push_back (t);
	}

	return is;
}
