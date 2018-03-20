#pragma once

#include <QDir>

#include "State.h"
#include "src\parser\Parser.h"
#include "src\view\GenericViewer.h"

class State;
class StateEditing;
class StateTraining;
class StateInitial;

class Controller
{
public:
	Controller ();
	virtual ~Controller ();

	//functions available for states

	Parser& getParser () { return parser; }

	GenericViewer* getViewer () { return viewer; }
	void setViewer (GenericViewer* viewer) { this->viewer = viewer; }

	QDir getFolderPath () { return currentDir; }
	void setFolderPath (QDir dir) { this->currentDir = dir; }

	void setCurrentState (State * state) { currentState = state; }
	State* getCurrentState () { return currentState; }
	StateInitial* getStateInitial () { return stateInitial; }
	StateEditing* getStateEditing () { return stateEditing; }
	StateTraining* getStateTraining () { return stateTraining; }

	// functions available for the viewer :

	void selectNewLessonFolder (QDir dir);
	void showLessons ();

	void showLesson (QFileInfo lessonFileInfo);

	void startTraining (QFileInfo lessonFileInfo);
	void answer (QString givenAnswer);
	void closeTraining ();

	void createNewLesson ();
	void editLesson ();
	void saveLesson ();
	void closeLesson ();
	void addNewTuple ();
	void deleteTuple ();

private:
	State *currentState;
	StateInitial *stateInitial;
	StateTraining *stateTraining;
	StateEditing *stateEditing;
	
	Parser parser;
	QDir currentDir = QDir::currentPath ();

	GenericViewer *viewer = NULL;
};