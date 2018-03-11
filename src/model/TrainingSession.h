#pragma once

#include <list>

#include "Lesson.h"
#include "Tuple.h"

class TrainingSession
{
public:
	TrainingSession (Lesson lesson);

	std::string getNext ();
	std::pair<Tuple, bool > answer (std::string);
	int getRemaining ();
	int getCorrectAnswers ();
	int getTotalAnswers ();
	bool isOver ();
	std::list<std::pair<Tuple, bool >> getAnswers () { return answeredTuples; }
	

private:
	Lesson m_lesson;

	// if the associated bool is false, the user must answer the translation
	// if the associated bool is true, the user must give the original word
	std::pair<Tuple, bool> tupleAsked;

	std::list<Tuple> unansweredTuples;
	std::list<std::pair<Tuple, bool >> answeredTuples;
};