#pragma once

#include <string>
#include <regex>

#define TUPLE_REGEX_STRING "[a-zäöüß\\s]+\\s:\\s[a-zàâçéèêëîïôûùüÿñæœ\\s]+"

/* Class Tuple:
	
	A tuple is a word and his traduction. It can also contain a context, to better understand the meaning
	of the word in the translated language
*/
class Tuple
{
public:
	Tuple () : m_translated (""), m_original ("") {}
	Tuple (std::string originalLanguageWord, std::string translatedLanguageWord) :
		m_original (originalLanguageWord),
		m_translated (translatedLanguageWord) {}

	//setters
	void setOriginal (std::string originalLanguageWord) { m_original = originalLanguageWord; }
	void setTranslated (std::string translatedLanguageWord) { m_translated = translatedLanguageWord; }

	//getters
	std::string getTranslated () { return m_translated; }
	std::string getOriginal () { return m_original; }
	bool isValid () { return m_valid; }

	//operators used to serialize / deserialize the object
	friend std::ostream& operator<<(std::ostream& stream, const Tuple& tuple);
	friend std::istream& operator>>(std::istream& is, Tuple& tuple);

protected:
	//regular expression used to deserialized, to see if the given input matches a Tuple

	std::string m_original;
	std::string m_translated;

	bool m_valid = false;
};
