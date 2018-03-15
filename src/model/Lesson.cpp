#include "Lesson.h"

Lesson::Lesson ()
{

}

QTextStream& operator<<(QTextStream& os, const Lesson& lesson)
{
	for (auto it : lesson.m_dictionnary)
	{
		os << it << endl;
	}

	return os;
}

QTextStream& operator>>(QTextStream& is, Lesson& lesson)
{
	// retrieving the number of lines == the number of tuples in our stream
	int lineCount = 0;
	while (!is.atEnd ())
	{
		is.readLine ();
		lineCount++;
	}
	
	lesson.m_dictionnary.reserve (lineCount +1);
	
	is.seek (0);

	//parsing the stream
	while (!is.atEnd())
	{
		Tuple t;
		is >> t;
		if(t.isValid())
			lesson.m_dictionnary.push_back (t);
	}

	return is;
}
