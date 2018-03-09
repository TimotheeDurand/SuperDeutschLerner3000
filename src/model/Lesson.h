#pragma once

#include <vector>
#include <exception>

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
	friend std::ostream& operator<< (std::ostream& stream, const Lesson& lesson);
	friend std::istream& operator>>(std::istream& is, Lesson& lesson);

protected:
	DictionnaryType m_dictionnary;
};