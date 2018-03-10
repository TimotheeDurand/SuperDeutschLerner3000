#pragma once

#include "State.h"

class StateInitial : public State
{
	virtual void selectNewLessonFolder (Controller & controller, std::string folderPath) const override;
	virtual void showLessons (Controller & controller) const override;
	virtual void startTraining (Controller & controller, std::string lessonFileName) const override;
};