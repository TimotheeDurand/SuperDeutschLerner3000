#include "Tuple.h"
#include <iostream>

QTextStream& operator<<(QTextStream& os, const Tuple& tuple)
{
	os << tuple.m_original << " : " << tuple.m_translated;
	return os;
}

QTextStream& operator>>(QTextStream& is, Tuple& tuple)
{
	static const QRegExp fullTupleRegex (QString::fromLocal8Bit (TUPLE_REGEX_STRING), Qt::CaseSensitivity::CaseInsensitive);

	bool failed = true;
	QString line = is.readLine();

	tuple.m_valid = fullTupleRegex.exactMatch (line);

	if (tuple.m_valid)
	{
		int pos = line.indexOf (':');
		if (pos > 0 && line.at(pos-1) == ' ')
		{
			tuple.m_original = line.mid (0, pos - 1);
		}

		if (pos + 2 < line.length () && line.at (pos + 1) == ' ')
		{
			tuple.m_translated = line.mid (pos+2);
		}
	}

	return is;
}
