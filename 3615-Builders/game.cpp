#include "game.hpp"


void game::chooseNewQuestion()
{
	currentQuestion = 1;
}

void game::startNewGame(uint8_t level, uint16_t numberQuestions)
{
	currentGameLevel = level;
	currentGameMaxQuestions = numberQuestions;
}