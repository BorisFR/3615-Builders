#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <Arduino.h>
#include "Qcm.hpp"

#define MAX_QUESTIONS 20

class Game
{

	private:
		uint8_t currentGameLevel;
		uint16_t currentGameMaxQuestions;
		uint8_t currentQuestion;
		int16_t questionsInGame[MAX_QUESTIONS];
		uint16_t indexReal;

		int16_t numberQuestionsByLevel[NUMBER_QCM_LEVEL];
		void parseQCM();

	public:
		void setup();
		void loop();
		void startNewGame(uint8_t level, uint16_t numberQuestions);
		void nextQuestion();
		String getCurrentQuestion();
		String getCurrentCategory();
		String getCurrentAnswer1();
		String getCurrentAnswer2();
		String getCurrentAnswer3();

};

#endif