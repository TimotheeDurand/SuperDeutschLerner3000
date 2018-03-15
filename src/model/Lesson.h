#pragma once

#include <vector>
#include <exception>

#include <QTextStream>
#include <QVector>
#include <QString>

#include "Tuple.h"

typedef QVector<Tuple> DictionnaryType;

/* Class Lesson:
	
	A Lesson is a list of tuples containing words and their traduction
*/
class Lesson
{
public:
	Lesson ();
	Lesson (DictionnaryType & dictionnary) : m_dictionnary(dictionnary) {}
	DictionnaryType & getDictionnary () { return m_dictionnary; }
	friend QTextStream& operator<< (QTextStream& stream, const Lesson& lesson);
	friend QTextStream& operator>>(QTextStream& is, Lesson& lesson);

protected:
	DictionnaryType m_dictionnary;
};