#pragma once
#ifndef MY_CONFIG_HPP
#define MY_CONFIG_HPP

#define PIN_MINITEL_SERIAL_TX 34
#define PIN_MINITEL_SERIAL_RX 33

enum PlayerStatus
{
	Sensitif,
	Padawan,
	Chevalier,
	Maitre,
	GrandMaitre
};

#define MAX_QUESTIONS_PER_GAME 20
#define SECONDS_TO_ANSWER 30 * 1000

#define SECRETCODE "boris"

#endif