#include "TrainingSession.h"

#include <algorithm>

TrainingSession::TrainingSession (Lesson lesson) : m_lesson (lesson)
{
	DictionnaryType dict = m_lesson.getDictionnary ();
	size_t size = m_lesson.getDictionnary ().size ();
	int *indexes = new int[dict.size ()];
	for (size_t i = 0; i < size; i++)
	{
		indexes[i] = i;
	}
	std::random_shuffle (&indexes[0], &indexes[size]);
	for (size_t i = 0; i < size; i++)
	{
		unansweredTuples.push_back (dict[indexes[i]]);
	}
}

std::string TrainingSession::getNext ()
{
	bool askTranslation = rand () % 2;

	tupleAsked = { unansweredTuples.front (), askTranslation };
	unansweredTuples.pop_front ();

	if (askTranslation)
		return tupleAsked.first.getOriginal ();
	return tupleAsked.first.getTranslated ();
}

std::pair<Tuple, bool > TrainingSession::answer (std::string givenAnswer)
{
	std::string stringAsked;

	if (tupleAsked.second)
		stringAsked = tupleAsked.first.getTranslated ();
	else
		stringAsked = tupleAsked.first.getOriginal ();

	answeredTuples.push_back ({ tupleAsked.first, stringAsked == givenAnswer });

	return answeredTuples.back();
}

int TrainingSession::getRemaining ()
{
	return unansweredTuples.size ();
}

bool TrainingSession::isOver ()
{
	return getRemaining() > 0;
}
