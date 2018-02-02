#pragma once
#ifndef THE_DISPLAY_HPP
#define THE_DISPLAY_HPP

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "MyConfig.hpp"
#include "Minitel.h"
#include "page_resultat.hpp"

enum MINITEL_PAGE
{
	PageAccueil,
	PageChoixNiveau,
	PageQuestion,
	PageAbandon,
	PageResultat
};

class TheDisplay
{
	private:
		Minitel minitel();
		void show(uint16_t size, const uint8_t bytes[]);

	public:
		void showPage(MINITEL_PAGE page);
		bool isKeyPress();

};

#endif