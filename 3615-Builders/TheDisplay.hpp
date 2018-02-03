#pragma once
#ifndef THE_DISPLAY_HPP
#define THE_DISPLAY_HPP

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ElapsedMillis.hpp"
#include "MyConfig.hpp"
#include "Minitel1B_Hard.h"
#include "page_resultat.hpp"
//#include "qcm.hpp"

#define MINITEL_SCREEN_TIMEOUT ((4 * 60 * 1000) - (5 * 1000)) // 4 minutes - 5 secondes

enum MINITEL_PAGE
{
	PageConfiguration,
	PageAccueil,
	PageChoixNiveau,
	PageQuestion,
	PageAbandon,
	PageResultat
};

class TheDisplay
{
	private:
		void sendBytes(uint16_t size, const uint8_t bytes[]);
		ElapsedMillis minitelTimeLastCommand;
		bool keyIsPressed;
		bool isTextKey(unsigned long);
		unsigned long lastKey;
		uint8_t getNumericInputNumber(uint8_t from, uint8_t to);

	public:
		void setup();
		void loop();

		void showPage(MINITEL_PAGE page);
		bool isKeyPress();
		bool isCancel();
		void showQuestion(uint8_t number, String category, String question, String answer1, String answer2, String answer3);
		uint8_t getLevel();
		uint8_t getAnswer();
		void showResult(uint8_t goodAnswers, uint8_t badAnswers, PlayerStatus status, String motto);

};

#endif