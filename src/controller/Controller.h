#pragma once

#include <QDir>

#include "State.h"
#include "src\parser\Parser.h"
#include "src\view\GenericViewer.h"
#include "model\TrainingSession.h"

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

	TrainingSession* getTrainingSession () { return trainingSession; }
	void setTrainingSession (TrainingSession* trainingSession) { this->trainingSession = trainingSession; }

	Lesson* getEditedLesson () { return editedLesson; }
	void setEditedLesson (Lesson* lesson) { editedLesson = lesson; }

	QFileInfo getEditedLessonFileInfo () { return editedLessonFileInfo; }
	void setEditedLessonFileInfo (QFileInfo infos) { editedLessonFileInfo = infos; }

	// functions available for the viewer :
	void selectNewLessonFolder (QDir dir);
	void showLessons ();
	void refreshLessons ();

	void showLesson (QFileInfo lessonFileInfo);

	void startTraining (QFileInfo lessonFileInfo);
	void answer (QString givenAnswer);
	void closeTraining ();

	void createNewLessonFile ();
	void renameLessonFile (QFileInfo lessonFileInfo, QString newName);
	void deleteLessonFile (QFileInfo lessonFileInfo);
	void editLesson (QFileInfo lessonFileInfo);
	void saveLesson ();
	void closeLesson ();
	void addNewTuple (QString original, QString translated);
	void deleteTuple (int idx);
	void editTuple (int idx, QString original, QString translated);

	static QString getFileExtention () { return DEFAULT_LESSON_FILE_EXTENSION; }

private:
	State *currentState;
	StateInitial *stateInitial;
	StateTraining *stateTraining;
	StateEditing *stateEditing;
	
	Parser parser;
	QDir currentDir = QDir::currentPath ();

	GenericViewer *viewer = nullptr;

	Lesson *editedLesson = nullptr;
	QFileInfo editedLessonFileInfo;
	TrainingSession* trainingSession = nullptr;
};