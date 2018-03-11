#pragma once

#include <string>
#include <filesystem>

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

	std::string getFolderPath () { return folderPath; }
	void setFolderPath (std::string folderPath ) { this->folderPath = folderPath; }

	void setCurrentState (State * state) { currentState = state; }
	State* getCurrentState () { return currentState; }
	StateInitial* getStateInitial () { return stateInitial; }
	StateEditing* getStateEditing () { return stateEditing; }
	StateTraining* getStateTraining () { return stateTraining; }

	// functions available for the viewer :

	void selectNewLessonFolder (std::string folderPath);
	void showLessons ();

	void startTraining (std::string lessonFileName);
	void answer (std::string givenAnswer);
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
	std::string folderPath = std::experimental::filesystem::current_path ().string();

	GenericViewer *viewer = NULL;
};