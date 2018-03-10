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

	Parser& getParser () { return parser; }
	GenericViewer* getViewer () { return viewer; }
	void setViewer (GenericViewer* viewer) { this->viewer = viewer; }

	std::string getFolderPath () { return folderPath; }
	void setFolderPath (std::string folderPath ) { this->folderPath = folderPath; }

	void setCurrentState (State * state) { currentState = state; }
	const State* getCurrentState () { return currentState; }
	const StateInitial* getStateInitial () { return stateInitial; }
	const StateEditing* getStateEditing () { return stateEditing; }
	const StateTraining* getStateTraining () { return stateTraining; }

	void selectNewLessonFolder (std::string folderPath);
	void showLessons ();

	void startTraining (std::string lessonFileName);
	void closeTraining ();

	void createNewLesson ();
	void editLesson ();
	void saveLesson ();
	void closeLesson ();
	void addNewTuple ();
	void deleteTuple ();

private:
	const State *currentState;
	const StateInitial *stateInitial;
	const StateTraining *stateTraining;
	const StateEditing *stateEditing;
	
	Parser parser;
	std::string folderPath = std::experimental::filesystem::current_path ().string();

	GenericViewer *viewer;
};