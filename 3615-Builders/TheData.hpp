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


	public:
		void setup();
		void listFiles();
		void saveScore(String gamertag, uint16_t points, String questions[MAX_QUESTIONS_PER_GAME], uint8_t answers[MAX_QUESTIONS_PER_GAME]);

};

#endif