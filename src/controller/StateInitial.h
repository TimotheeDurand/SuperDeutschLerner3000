#pragma once

#include "State.h"

class StateInitial : public State
{
	virtual void selectNewLessonFolder (Controller & controller, QDir dir) const override;
	virtual void showLessons (Controller & controller) const override;
	virtual void startTraining (Controller & controller, QFileInfo lessonFileInfo) const override;
	virtual void showLesson (Controller & controller, QFileInfo lessonFileInfo) const override;
};