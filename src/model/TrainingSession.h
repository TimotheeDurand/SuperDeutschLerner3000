#pragma once

#include <list>
#include <QList>
#include <QPair>

#include "Lesson.h"
#include "Tuple.h"

class TrainingSession
{
public:
	TrainingSession (Lesson lesson);

	QString getNext ();
	QPair<Tuple, bool > answer (QString givenAnswer);
	int getRemaining ();
	int getCorrectAnswers ();
	int getTotalAnswers ();
	bool isOver ();
	QList<QPair<Tuple, bool >> getAnswers () { return answeredTuples; }
	

private:
	Lesson m_lesson;

	// if the associated bool is false, the user must answer the translation
	// if the associated bool is true, the user must give the original word
	QPair<Tuple, bool> tupleAsked;

	QList<Tuple> unansweredTuples;
	QList<QPair<Tuple, bool >> answeredTuples;
};