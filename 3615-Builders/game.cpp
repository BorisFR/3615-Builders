#include "Game.hpp"

void Game::setup()
{
	parseQCM();
}

void Game::loop()
{

}

void Game::parseQCM()
{
	for(uint8_t i = 0; i < NUMBER_QCM_LEVEL; i++)
	{
		numberQuestionsByLevel[i] = 0;
	}

	for(uint8_t i = 0; i < NUMBER_QCM_QUESTIONS; i++)
	{
		numberQuestionsByLevel[qcmLevel[i]]++;
	}
}

void Game::startNewGame(uint8_t level, uint16_t numberQuestions)
{
	currentGameLevel = level;
	currentGameMaxQuestions = numberQuestions;
	for(uint8_t i = 0; i < MAX_QUESTIONS; i++)
	{
		questionsInGame[i] = -1;
	}
	currentQuestion = 0;
}

void Game::nextQuestion()
{
	currentQuestion++;
}

String Game::getCurrentQuestion()
{
	return qcmQuestions[indexReal];
}

String Game::getCurrentCategory()
{
	switch(qcmCategories[indexReal])
	{
		case 0: return "Cinéma";
		case 1: return "Connaissance";
		case 2: return "Droïde";
		case 3: return "Histoire";
	}
	return String(qcmCategories[indexReal]);
}

String Game::getCurrentAnswer1()
{
	return qcmAnswers[indexReal];
}

String Game::getCurrentAnswer2()
{
	return qcmFalse1[indexReal];
}

String Game::getCurrentAnswer3()
{
	return qcmFalse2[indexReal];
}
