#pragma once

#include <string>

#include "Controller.h"

class Controller;

class State
{
public:
	virtual void selectNewLessonFolder (Controller & controller, std::string folderPath) const {}
	virtual void showLessons (Controller & controller) const {}

	virtual void startTraining (Controller & controller, std::string lessonFileName) const {}
	virtual void answer (Controller & controller, std::string givenAnswer) const {}
	virtual void closeTraining (Controller & controller) const {}
	

	virtual void createNewLesson () const {}
	virtual void editLesson () const {}
	virtual void saveLesson () const {}
	virtual void closeLesson () const {}

	virtual void addNewTuple () const {}
	virtual void deleteTuple () const {}
};