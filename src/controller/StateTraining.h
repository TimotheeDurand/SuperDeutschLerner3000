#pragma once

#include "State.h"

#include "src\model\TrainingSession.h"

class StateTraining : public State
{
public:
	void createTrainingSession (Controller &controller, Lesson &lesson);
	virtual void answer (Controller & controller, std::string givenAnswer) const override;
	virtual void closeTraining (Controller & controller) const override;

protected:
	TrainingSession* currentTrainingSession = NULL;
};