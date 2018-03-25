#include "StateTraining.h"
#include <tuple>

void StateTraining::createTrainingSession (Controller &controller, Lesson &lesson)
{
	if (controller.getTrainingSession())
		delete controller.getTrainingSession ();
	TrainingSession* currentTrainingSession = new TrainingSession(lesson);
	controller.setTrainingSession (currentTrainingSession);
	if (!currentTrainingSession->isOver ())
	{
		auto[word, original] = currentTrainingSession->getNext ();
		controller.getViewer ()->askWord (word, original);
	}
	else
	{
		controller.getViewer ()->showTrainingEnded (
			currentTrainingSession->getCorrectAnswers (),
			currentTrainingSession->getTotalAnswers (),
			currentTrainingSession->getAnswers ());
		controller.setCurrentState ((State*)controller.getStateInitial ());
	}
}

void StateTraining::answer (Controller & controller, QString givenAnswer) const
{
	
	TrainingSession* currentTrainingSession = controller.getTrainingSession ();
	auto [tuple, wellAnswered, unused] = currentTrainingSession->answer (givenAnswer);
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
	TrainingSession* currentTrainingSession = controller.getTrainingSession ();
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
