#include <Arduino.h>
#include "Game.hpp"

Game game;

enum ProgramStatus
{
	displayWelcome,
	waitForKeypress,
	displayChooseLevel,
	waitForLevel,
	initNewGame,
	displayQuestion,
	waitForAnswer,
	displayResult,
	waitForEnding
} programStatus;

void setup() {
	game.setup();
	programStatus = displayWelcome;
}

void loop() {
	game.loop();
	switch(programStatus)
	{
		case displayWelcome:
			//
			programStatus = waitForKeypress;
			break;
		case waitForKeypress:
			//
			//programStatus = displayChooseLevel;
			break;
		case displayChooseLevel:
			//
			programStatus = waitForLevel;
			break;
		case waitForLevel:
			//
			//programStatus = initNewGame;
			break;
		case initNewGame:
			game.startNewGame(1, 20);
			programStatus = displayQuestion;
			break;
		case displayQuestion:
			//
			programStatus = waitForAnswer;
			break;
		case waitForAnswer:
			//
			//programStatus = displayResult;
			break;
		case displayResult:
			//
			programStatus = waitForEnding;
			break;
		case waitForEnding:
			//
			//programStatus = displayWelcome;
			break;
	}
}