#pragma once

#include <vector>

#include "Tuple.h"

typedef std::vector<Tuple> DictionnaryType;

/* Class Lesson:
	
	A Lesson is a list of tuples containing words and their traduction
*/
class Lesson
{
public:
	Lesson ();
	Lesson (DictionnaryType & dictionnary) : m_dictionnary(dictionnary) {}
	DictionnaryType & getDictionnary () { return m_dictionnary; }
	friend std::ostream& operator<< (std::ostream& stream, const Lesson& tuple);
	friend std::istream& operator>>(std::istream& is, Tuple& tuple);

protected:
	DictionnaryType m_dictionnary;
};
