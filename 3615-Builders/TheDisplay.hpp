#pragma once
#ifndef THE_DISPLAY_HPP
#define THE_DISPLAY_HPP

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ElapsedMillis.hpp"
#include "MyConfig.hpp"
#include "Minitel1B_Hard.h"
#include "page_accueil.hpp"
#include "page_difficulte.hpp"
#include "page_question.hpp"
#include "page_resultat.hpp"
#include "page_header.hpp"
#include "rang_human.hpp"
#include "rang_initie.hpp"
#include "rang_sensitif.hpp"
#include "rang_padawan.hpp"
#include "rang_chevalier.hpp"
#include "rang_maitre.hpp"

#define MINITEL_SCREEN_TIMEOUT ((4 * 60 * 1000) - (5 * 1000)) // 4 minutes - 5 secondes

enum MINITEL_PAGE
{
	PageConfiguration,
	PageAccueil,
	PageChoixNiveau,
	PageSaisieNom,
	PageQuestion,
	PageAbandon,
	PageResultat
};

class TheDisplay
{
	private:
		void sendBytes(uint16_t size, const uint8_t bytes[]);
		//ElapsedMillis minitelTimeLastCommand;
		bool keyIsPressed;
		bool isTextKey(unsigned long);
		unsigned long lastKey;
		uint8_t getNumericInputNumber(uint8_t from, uint8_t to);
		void writeTextOn(String text, uint8_t width);
		void writeTextInBox(String text, uint8_t x, uint8_t y, uint8_t width, uint8_t height, byte color);
		uint8_t memoChrono;
		uint8_t posX;
		uint8_t posY;
		void writeCenter(String text, uint8_t y, byte color, bool blink);
		bool isInInputTextMode;
		uint8_t maxInputSize;
		String theInput;
		bool resetTimer;
		bool inputIsReady;

		void startInput(uint8_t size);

	  public:
		void setup();
		void loop();

		void showPage(MINITEL_PAGE page);
		bool isKeyPress();
		bool isCancel();
		void showQuestion(uint8_t number, uint8_t level, String category, String question, String answer1, String answer2, String answer3);
		bool displayChrono(uint8_t value);
		uint8_t getLevel();
		uint8_t getAnswer();
		void showResult(uint8_t goodAnswers, uint8_t badAnswers, PlayerStatus status, String motto);
		String getInputValue();
		bool isInputReady();

};

#endif