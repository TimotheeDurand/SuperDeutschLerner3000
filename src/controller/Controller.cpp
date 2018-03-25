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

void Controller::refreshLessons ()
{
	currentState->refreshLessons (*this);
}

void Controller::showLesson (QFileInfo lessonFileInfo)
{
	currentState->showLesson (*this, lessonFileInfo);
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

void Controller::createNewLessonFile ()
{
	currentState->createNewLessonFile (*this);
}

void Controller::renameLessonFile (QFileInfo lessonFileInfo, QString newName)
{
	currentState->renameLessonFile (*this, lessonFileInfo, newName);
}

void Controller::deleteLessonFile (QFileInfo lessonFileInfo)
{
	currentState->deleteLessonFile (*this, lessonFileInfo);
}

void Controller::editLesson (QFileInfo lessonFileInfo)
{
	currentState->editLesson (*this, lessonFileInfo);
}

void Controller::saveLesson ()
{
	currentState->saveLesson (*this);
}

void Controller::closeLesson ()
{
	currentState->closeLesson (*this);
}

void Controller::addNewTuple (QString original, QString translated)
{
	currentState->addNewTuple (*this, original, translated);
}

void Controller::deleteTuple (int idx)
{
	currentState->deleteTuple (*this, idx);
}

void Controller::editTuple (int idx, QString original, QString translated)
{
	currentState->editTuple (*this, idx, original, translated);
}