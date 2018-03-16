#include "StateTraining.h"

void StateTraining::createTrainingSession (Controller &controller, Lesson &lesson)
{
	if (currentTrainingSession)
		delete currentTrainingSession;
	currentTrainingSession = new TrainingSession(lesson);
	controller.getViewer ()->askWord (currentTrainingSession->getNext ());
}

void StateTraining::answer (Controller & controller, QString givenAnswer) const
{
	auto [tuple, wellAnswered, ga] = currentTrainingSession->answer (givenAnswer);
	controller.getViewer ()->giveAnswer (tuple.getOriginal (), tuple.getTranslated(), wellAnswered);

	if (!currentTrainingSession->isOver())
	{
		controller.getViewer ()->askWord (currentTrainingSession->getNext ());
	}
	else
	{
		controller.getViewer ()->showTrainingEnded (
			currentTrainingSession->getCorrectAnswers (),
			currentTrainingSession->getTotalAnswers (),
			currentTrainingSession->getAnswers());
		controller.setCurrentState ((State*)controller.getStateInitial ());
	}
}

void StateTraining::closeTraining (Controller & controller) const
{
	controller.getViewer ()->showTrainingEnded (
		currentTrainingSession->getCorrectAnswers (),
		currentTrainingSession->getTotalAnswers (),
		currentTrainingSession->getAnswers());
	controller.setCurrentState ((State*)controller.getStateInitial ());
}
