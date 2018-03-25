#pragma once

#include <QRegExp>
#include <QString>
#include <QTextStream>

#define TUPLE_REGEX_STRING "[a-zäöüß\',!\\?\\.\\s]+\\s:\\s[a-zàâçéèêëîïôûùüÿæœ\',!\\?\\.\\s]+"

/* Class Tuple:
	
	A tuple is a word and his traduction. It can also contain a context, to better understand the meaning
	of the word in the translated language
*/
class Tuple
{
public:
	Tuple () : m_translated (""), m_original ("") {}
	Tuple (QString originalLanguageWord, QString translatedLanguageWord) :
		m_original (originalLanguageWord),
		m_translated (translatedLanguageWord) {}

	//setters
	void setOriginal (QString originalLanguageWord) { m_original = originalLanguageWord; }
	void setTranslated (QString translatedLanguageWord) { m_translated = translatedLanguageWord; }

	//getters
	QString getTranslated () const { return m_translated; }
	QString getOriginal () const { return m_original; }
	bool isValid () { return m_valid; }

	//operators used to serialize / deserialize the object
	friend QTextStream& operator<<(QTextStream& stream, const Tuple& tuple);
	friend QTextStream& operator>>(QTextStream& is, Tuple& tuple);

protected:
	//regular expression used to deserialized, to see if the given input matches a Tuple

	QString m_original;
	QString m_translated;

	bool m_valid = false;
};
