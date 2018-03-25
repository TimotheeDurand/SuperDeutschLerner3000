#pragma once

#include "State.h"

#include "model\Lesson.h"

class StateEditing : public State
{
public:
	virtual void addNewTuple (Controller & controller, QString original, QString translated) const override;
	virtual void deleteTuple (Controller & controller, int idx) const override;
	virtual void editTuple (Controller & controller, int idx, QString original, QString translated) const override;
	virtual void saveLesson (Controller & controller) const override;
	virtual void closeLesson (Controller & controller) const override;
};