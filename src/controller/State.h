#pragma once

#include <string>

#include "Controller.h"

class Controller;

class State
{
public:
	virtual void selectNewLessonFolder (Controller & controller, QDir dir) const {}
	virtual void showLessons (Controller & controller) const {}
	virtual void refreshLessons (Controller & controller) const {}

	virtual void showLesson (Controller & controller, QFileInfo lessonFileInfo) const {}

	virtual void startTraining (Controller & controller, QFileInfo lessonFileInfo) const {}
	virtual void answer (Controller & controller, QString givenAnswer) const {}
	virtual void closeTraining (Controller & controller) const {}
	

	virtual void createNewLessonFile (Controller & controller) const {}
	virtual void renameLessonFile (Controller & controller, QFileInfo lessonFileInfo, QString newName) const {}
	virtual void deleteLessonFile (Controller & controller, QFileInfo lessonFileInfo) const {}
	virtual void editLesson (Controller & controller, QFileInfo lessonFileInfo) const {}
	virtual void saveLesson (Controller & controller) const {}
	virtual void closeLesson (Controller & controller) const {}

	virtual void addNewTuple (Controller & controller, QString original, QString translated) const {}
	virtual void deleteTuple (Controller & controller, int idx) const {}
	virtual void editTuple (Controller & controller, int idx, QString original, QString translated) const {}
};