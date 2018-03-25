#pragma once

#include "State.h"

class StateInitial : public State
{
	virtual void selectNewLessonFolder (Controller & controller, QDir dir) const override;
	virtual void showLessons (Controller & controller) const override;
	virtual void startTraining (Controller & controller, QFileInfo lessonFileInfo) const override;
	virtual void showLesson (Controller & controller, QFileInfo lessonFileInfo) const override;
	virtual void createNewLessonFile (Controller & controller) const override;
	virtual void renameLessonFile (Controller & controller, QFileInfo lessonFileInfo, QString newName) const override;
	virtual void deleteLessonFile (Controller & controller, QFileInfo lessonFileInfo) const override;
	virtual void refreshLessons (Controller & controller) const override;
	virtual void editLesson (Controller & controller, QFileInfo lessonFileInfo) const override;
};