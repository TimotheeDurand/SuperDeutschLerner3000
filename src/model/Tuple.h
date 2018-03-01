#pragma once

#include <string>
#include <regex>

#define TUPLE_REGEX_STRING "([A-Za-zßüöÖÜ]+ )+: ([A-Za-zéèçàùÀÉÈëË ]+ )+"

/* Class Tuple:
	
	A tuple is a word and his traduction. It can also contain a context, to better understand the meaning
	of the word in the translated language
*/
class Tuple
{
public:
	Tuple (std::string originalLanguageWord, std::string translatedLanguageWord) :
		m_originalLanguageWord (originalLanguageWord),
		m_translatedLanguageWord (translatedLanguageWord) {}

	//setters
	void setOLW (std::string& originalLanguageWord) { m_originalLanguageWord = originalLanguageWord; }
	void setTLW (std::string& translatedLanguageWord) { m_translatedLanguageWord = translatedLanguageWord; }

	//getters
	std::string getTLW () { return m_translatedLanguageWord; }
	std::string getOLW () { return m_originalLanguageWord; }

	//operators used to serialize / deserialize the object
	friend std::ostream& operator<<(std::ostream& stream, const Tuple& tuple);
	friend std::istream& operator>>(std::istream& is, Tuple& tuple);

protected:
	//regular expression used to deserialized, to see if the given input matches a Tuple

	std::string m_originalLanguageWord;
	std::string m_translatedLanguageWord;
};
