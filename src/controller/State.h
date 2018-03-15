#pragma once

#include <string>

#include "Controller.h"

class Controller;

class State
{
public:
	virtual void selectNewLessonFolder (Controller & controller, QDir dir) const {}
	virtual void showLessons (Controller & controller) const {}

	virtual void startTraining (Controller & controller, QFileInfo lessonFileInfo) const {}
	virtual void answer (Controller & controller, QString givenAnswer) const {}
	virtual void closeTraining (Controller & controller) const {}
	

	virtual void createNewLesson () const {}
	virtual void editLesson () const {}
	virtual void saveLesson () const {}
	virtual void closeLesson () const {}

	virtual void addNewTuple () const {}
	virtual void deleteTuple () const {}
};