#pragma once
#ifndef THE_DATA_HPP
#define THE_DATA_HPP

#include <Arduino.h>
#include <TimeLib.h>
#include <SD.h>
#include "MyConfig.hpp"

class TheData
{

	private:
		uint8_t convertValue[62];
		bool isStatusOk;
		void printDirectory(File dir, int numTabs);
		String on2(uint8_t value);
		String convertFrom(uint8_t value);
		int8_t insertInBoard(String name, uint16_t points);


	public:
		void setup();
		void loadScores();
		void listFiles();
		void saveScore(String gamertag, uint16_t points, String questions[MAX_QUESTIONS_PER_GAME], uint8_t answers[MAX_QUESTIONS_PER_GAME]);

		String hiscoresName[MAX_SCORES];
		uint16_t hiscoresPoints[MAX_SCORES];

};

#endif