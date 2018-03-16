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
	std::tuple<Tuple, bool, QString> answer (QString givenAnswer);
	int getRemaining ();
	int getCorrectAnswers ();
	int getTotalAnswers ();
	bool isOver ();
	QList<std::tuple<QString, QString, bool, QString>> getAnswers ();
	

private:
	Lesson m_lesson;

	// if the associated bool is false, the user must answer the translation
	// if the associated bool is true, the user must give the original word
	QPair<Tuple, bool> tupleAsked;

	QList<Tuple> unansweredTuples;
	QList<std::tuple<Tuple, bool, QString>> answeredTuples;
};