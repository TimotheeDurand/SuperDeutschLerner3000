#pragma once

#include "State.h"

class StateTraining : public State
{
public:
	void createTrainingSession (Controller &controller, Lesson &lesson);
	virtual void answer (Controller & controller, QString givenAnswer) const override;
	virtual void closeTraining (Controller & controller) const override;
};