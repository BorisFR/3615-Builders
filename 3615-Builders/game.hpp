#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <Arduino.h>
#include "qcm.hpp"

#define MAX_QUESTIONS 20

class game
{

	private:
		uint8_t currentGameLevel;
		uint16_t currentGameMaxQuestions;
		uint16_t currentQuestion;
		uint16_t questionsInGame[MAX_QUESTIONS];

	public:
		void chooseNewQuestion();
		void startNewGame(uint8_t level, uint16_t numberQuestions);

};

#endif