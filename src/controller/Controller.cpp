#include "Controller.h"

#include "src\controller\StateInitial.h"
#include "src\controller\StateEditing.h"
#include "src\controller\StateTraining.h"

Controller::Controller ()
{
	stateInitial = new StateInitial;
	stateTraining = new StateTraining;
	stateEditing = new StateEditing;

	currentState = stateInitial;
}

Controller::~Controller ()
{
	delete stateInitial;
	delete stateTraining;
	delete stateEditing;
}

void Controller::selectNewLessonFolder (QDir dir)
{
	currentState->selectNewLessonFolder (*this, dir);
}

void Controller::showLessons ()
{
	currentState->showLessons (*this);
}

void Controller::startTraining (QFileInfo lessonFileInfo)
{
	currentState->startTraining (*this, lessonFileInfo);
}

void Controller::answer (QString givenAnswer)
{
	currentState->answer (*this, givenAnswer);
}

void Controller::closeTraining ()
{
	currentState->closeTraining (*this);
}

void Controller::createNewLesson ()
{
	currentState->createNewLesson ();
}

void Controller::editLesson ()
{
	currentState->editLesson ();
}

void Controller::saveLesson ()
{
	currentState->saveLesson ();
}

void Controller::closeLesson ()
{
	currentState->closeLesson ();
}

void Controller::addNewTuple ()
{
	currentState->addNewTuple ();
}

void Controller::deleteTuple ()
{
	currentState->deleteTuple ();
}
