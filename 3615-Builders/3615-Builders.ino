#include <Arduino.h>
#include "ElapsedMillis.hpp"
#include "MyConfig.hpp"
#include "Game.hpp"
#include "TheDisplay.hpp"

Game game;
TheDisplay display;

enum ProgramStatus
{
	DisplayWelcome,
	WaitForKeypress,
	DisplayChooseLevel,
	WaitForLevel,
	InitNewGame,
	DisplayQuestion,
	WaitForAnswer,
	DisplayResult,
	WaitForEnding,
	DisplaySorry
} programStatus;

ElapsedMillis timeout;

void setup() {
	game.setup();
	programStatus = DisplayWelcome;
}

void loop() {
	game.loop();
	switch(programStatus)
	{
		// on affiche la page d'accueil
		case DisplayWelcome:
			display.showPage(PageAccueil);
			programStatus = WaitForKeypress;
			timeout = 0;
			break;
		// attente que quelqu'un se manifeste...
		case WaitForKeypress:
			// personne n'interagit
			if(timeout > SECONDS_TO_ANSWER) {
				// juste ré-affiche la page
				// on peut imaginer faire des animations...
				programStatus = DisplayWelcome;
				break;
			}
			// TODO: gérer le code secret pour l'écran de configuration
			if(display.isKeyPress())
			{
				programStatus = DisplayChooseLevel;
				break;
			}
			break;
		// quelqu'un est là, on affiche le choix du niveau
		case DisplayChooseLevel:
			display.showPage(PageChoixNiveau);
			programStatus = WaitForLevel;
			timeout = 0;
			break;
		// attente du choix de niveau
		case WaitForLevel:
			// choix non fait, on abandonne le début du jeu
			// et on ré-affiche la page d'accueil
			if(timeout > SECONDS_TO_ANSWER) {
				programStatus = DisplayWelcome;
				break;
			}
			//programStatus = InitNewGame;
			break;
		// le choix du niveau est fait
		// on affiche l'écran des questions
		case InitNewGame:
			game.startNewGame(1, 20);
			programStatus = DisplayQuestion;
			display.showPage(PageQuestion);
			break;
		// on affiche une question
		case DisplayQuestion:
			// TODO: afficher la question
			programStatus = WaitForAnswer;
			timeout = 0;
			break;
		// on attend la réponse du joueur
		case WaitForAnswer:
			// il n'a pas répondu dans les temps
			// le jeu est terminé !
			if(timeout > SECONDS_TO_ANSWER) {
				programStatus = DisplaySorry;
				break;
			}
			//programStatus = DisplayResult;
			break;
		// le joueur n'a pas répondu
		// on lui affiche qu'il a perdu
		case DisplaySorry:
			display.showPage(PageAbandon);
			programStatus = WaitForEnding;
			timeout = 0;
			break;
		// le joueur a répondu à toutes les questions
		// on affiche le résultat
		case DisplayResult:
			display.showPage(PageResultat);
			// TODO: afficher le résultat
			programStatus = WaitForEnding;
			timeout = 0;
			break;
		// on attend l'appui sur une touche
		// ou le timeout
		// pour retourner à l'accueil
		case WaitForEnding:
			if(timeout > SECONDS_TO_ANSWER)
			{
				programStatus = DisplayWelcome;
				break;
			}
			if(display.isKeyPress())
			{
				programStatus = DisplayWelcome;
				break;
			}
			break;
	}
}