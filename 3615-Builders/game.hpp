#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <Arduino.h>
#include "Qcm.hpp"
#include "MyConfig.hpp"
#include "ElapsedMillis.hpp"

// int16 => max 32000 questions
// uint8 => max 255 questions per game

class Game
{

	private:
		uint8_t startLevel;
		uint8_t currentLevel;
		uint16_t currentMaxQuestions;
		uint8_t currentQuestion;
		uint8_t currentGoodAnswer;
		bool giveGoodAnswer;
		String answer1;
		String answer2;
		String answer3;
		uint16_t indexReal;
		uint8_t countSuccessiveGood;
		uint8_t countSuccessiveBad;

		uint8_t goodAnswers;
		uint8_t badAnswers;
		uint16_t points;
		ElapsedMillis timeToAnswer;

		uint16_t numberQuestionsByLevel[NUMBER_QCM_LEVEL];
		uint16_t questionByLevel[NUMBER_QCM_LEVEL][MAX_QUESTIONS_BY_LEVEL];
		void parseQCM();
		void prepareOneQuestion();
		bool isAlreadyAsk(uint16_t indexQuestion);

	public:
		void setup();
		void loop();
		void startNewGame(uint8_t level, uint16_t numberQuestions);
		void nextQuestion();
		bool isGameFinish();
		uint8_t getCurrentQuestionNumber();
		uint8_t getCurrentQuestionLevel();
		String getCurrentQuestion();
		String getCurrentCategory();
		String getCurrentAnswer1();
		String getCurrentAnswer2();
		String getCurrentAnswer3();
		void playAnswer(uint8_t answer);
		bool isAnswerGood();

		uint8_t getNumberOfGoodAnswers();
		uint8_t getNumberOfBadAnswers();
		PlayerStatus getPlayerStatus();
		String getPlayerMotto();
		uint16_t getPoints();

		int16_t questionsInGame[MAX_QUESTIONS_PER_GAME];
		uint8_t answerinGame[MAX_QUESTIONS_PER_GAME];
		String questionsID[MAX_QUESTIONS_PER_GAME];

};

#endif