#include "StateEditing.h"

#include <QFileInfo>

void StateEditing::addNewTuple (Controller & controller, QString original, QString translated) const
{
	Lesson* lesson = controller.getEditedLesson ();
	QString buffer;
	QTextStream textStream (&buffer);
	textStream << original << " : " << translated;
	Tuple newTuple;
	textStream >> newTuple;
	if (newTuple.isValid ())
	{
		lesson->getDictionnary ().push_back (newTuple);
		controller.getViewer ()->showTupleAdded (original, translated, lesson->getDictionnary ().size ());
	}
	else
	{
		controller.getViewer ()->showTupleInvalid ("", "", lesson->getDictionnary ().size());
	}	
}

void StateEditing::deleteTuple (Controller & controller, int idx) const
{
	Lesson* lesson = controller.getEditedLesson ();
	if (idx > 0 && idx < lesson->getDictionnary ().size ())
	{
		lesson->getDictionnary ().removeAt (idx);
	}
}

void StateEditing::editTuple (Controller & controller, int idx, QString original, QString translated) const
{
	Lesson* lesson = controller.getEditedLesson ();
	QString buffer;
	QTextStream textStream(&buffer);
	textStream << original << " : " << translated;
	Tuple newTuple;
	textStream >> newTuple;
	if (idx > 0 && idx < lesson->getDictionnary ().size ())
	{
		if (newTuple.isValid ())
		{
			lesson->getDictionnary ().removeAt (idx);
			lesson->getDictionnary ().insert (idx, newTuple);
			controller.getViewer ()->showTupleAdded (original, translated, idx);
		}
		else
		{
			const Tuple& oldTuple = lesson->getDictionnary ().at (idx);
			controller.getViewer ()->showTupleInvalid (oldTuple.getOriginal(), oldTuple.getTranslated(), idx);
		}
	}
	else
	{
		controller.getViewer ()->showTupleInvalid ("", "", lesson->getDictionnary ().size ());
	}
}

void StateEditing::saveLesson (Controller & controller) const
{
	Lesson* lesson = controller.getEditedLesson ();
	Parser::IOStatus status = controller.getParser ().writeFile (*lesson, controller.getEditedLessonFileInfo ());
	if (status == Parser::IOStatus::CANNOT_OPEN_FILE)
	{
		controller.getViewer ()->showFileError (controller.getEditedLessonFileInfo (), GenericViewer::FileError::CANNOT_WRITE);
	}
	else
	{
		controller.getViewer ()->showLessonSaved (controller.getEditedLessonFileInfo());
	}
}

void StateEditing::closeLesson (Controller & controller) const
{
	controller.getViewer ()->showLessonClosed (controller.getEditedLessonFileInfo());
	controller.setCurrentState ((State*)controller.getStateInitial ());
	controller.showLesson (controller.getEditedLessonFileInfo ());
}
