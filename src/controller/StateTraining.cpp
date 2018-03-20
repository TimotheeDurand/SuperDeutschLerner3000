#include "StateTraining.h"

void StateTraining::createTrainingSession (Controller &controller, Lesson &lesson)
{
	if (currentTrainingSession)
		delete currentTrainingSession;
	currentTrainingSession = new TrainingSession(lesson);
	auto[word, original] = currentTrainingSession->getNext ();
	controller.getViewer ()->askWord (word, original);
}

void StateTraining::answer (Controller & controller, QString givenAnswer) const
{
	auto [tuple, wellAnswered, ga] = currentTrainingSession->answer (givenAnswer);
	controller.getViewer ()->giveAnswer (tuple.getOriginal (), tuple.getTranslated(), wellAnswered);

	if (!currentTrainingSession->isOver())
	{
		auto[word, original] = currentTrainingSession->getNext ();
		controller.getViewer ()->askWord (word, original);
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
	if (!currentTrainingSession->isOver ())
	{
		auto[tuple, wellAnswered, ga] = currentTrainingSession->answer ("");
		controller.getViewer ()->giveAnswer (tuple.getOriginal (), tuple.getTranslated (), wellAnswered);
	}
	controller.getViewer ()->showTrainingEnded (
		currentTrainingSession->getCorrectAnswers (),
		currentTrainingSession->getTotalAnswers (),
		currentTrainingSession->getAnswers());
	controller.setCurrentState ((State*)controller.getStateInitial ());
}
