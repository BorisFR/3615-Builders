#pragma once
#ifndef THE_DISPLAY_HPP
#define THE_DISPLAY_HPP

#include <Arduino.h>
#include <TimeLib.h>
#include <SoftwareSerial.h>
#include "ElapsedMillis.hpp"
#include "qrcode.h"
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
#include "hall_of_fame.hpp"

#define MINITEL_SCREEN_TIMEOUT ((4 * 60 * 1000) - (5 * 1000)) // 4 minutes - 5 secondes

enum MINITEL_PAGE
{
	PageConfiguration,
	PageScores,
	PageAccueil,
	PageChoixNiveau,
	PageSaisieNom,
	PageQuestion,
	PageAbandon,
	PageResultat,
	PageQRcode
};

class TheDisplay
{
	private:
	  QRCode qrcode;
	  void generateQrCode(String value);
	  String lines[QR_CODE_SIZE];
	  String on2(uint8_t value);
	  String weekDays[7] = {SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};
	  String monthsName[12] = {JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};
	  void sendBytes(uint16_t size, const uint8_t bytes[]);
	  //ElapsedMillis minitelTimeLastCommand;
	  bool keyIsPressed;
	  bool isTextKey(unsigned long);
	  unsigned long lastKey;
	  uint8_t getNumericInputNumber(uint8_t from, uint8_t to);
	  void writeTextRight(String text, uint8_t width);
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
	  int8_t scoreToHighlight;

	  void startInput(uint8_t size);

	  uint16_t scores[MAX_SCORES];
	  String gamertag[MAX_SCORES];

	  String gamerName;
	  uint16_t gamerPoints;
	  bool showQRcode;
	  uint8_t playerOnPodium;
	  uint8_t midi;

	public:
		void setup();
	 	void loop();

		void bip();
		void clearHiScores();
		void showPage(MINITEL_PAGE page);
		bool isKeyPress();
		bool isCancel();
		void clearKeyboard();
		void showQuestion(uint8_t number, uint8_t level, String category, String question, String answer1, String answer2, String answer3);
		bool displayChrono(uint8_t value);
		uint8_t getLevel();
		uint8_t getAnswer();
		void showResult(String gamer, uint8_t goodAnswers, uint8_t badAnswers, PlayerStatus status, String motto, uint16_t points);
		String getInputValue();
		bool isInputReady();
		bool onPodium();
		char getTextKey();
		void setQRcodeDisplay(bool value);
		void setHiScore(uint8_t place, String name, uint16_t points);
		void setPlayerPodium(uint8_t value);
		void setMidi(uint8_t value);
};

#endif