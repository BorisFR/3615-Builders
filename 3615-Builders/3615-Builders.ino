#include <Arduino.h>
#include "ElapsedMillis.hpp"
#include "MyConfig.hpp"
#include "Game.hpp"
#include "TheDisplay.hpp"

// ce qui gère le QCM
Game game;
// ce qui gère le lien avec le Minitel
TheDisplay display;

// les différents états du programme
enum ProgramStatus
{
	DisplayConfiguration,
	EntryConfiguration,
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

// pour gérer le fait qu'un joueur quitte en cours de route
ElapsedMillis timeout;

uint8_t playerAnswer;
uint8_t playerLevel;

#ifdef DEBUG
void debug(String text)
{
	Serial.println(text);
}
#endif

// initialisation globale du programme
void setup()
{
#ifdef DEBUG
	Serial.begin(115200);
	debug("3615 Builders starting...");
#endif
	game.setup();
	display.setup();
	programStatus = DisplayWelcome;
#ifdef DEBUG
	debug("3615 Builders ready!");
#endif
}

// boucle sans fin du jeu
void loop()
{
	game.loop();
	display.loop();

	// le boulot à faire en fonction de l'état en cours
	switch (programStatus)
	{
	// on affiche la page d'accueil
	case DisplayWelcome:
#ifdef DEBUG
		debug("[Display] welcome screen");
#endif
		display.showPage(PageAccueil);
		programStatus = WaitForKeypress;
		timeout = 0;
#ifdef DEBUG
		debug("[State] wait for a keypress");
#endif
		break;

	// attente que quelqu'un se manifeste...
	case WaitForKeypress:
		// personne n'interagit
		if (timeout > SECONDS_TO_ANSWER)
		{
#ifdef DEBUG
			debug("[State] time out!");
#endif
			// juste ré-affiche la page
			// on peut imaginer faire des animations...
			programStatus = DisplayWelcome;
			break;
		}
		// TODO: gérer le code secret pour l'écran de configuration
		if (display.isKeyPress())
		{
			programStatus = DisplayChooseLevel;
			break;
		}
		break;

	// on affiche la page de configuration du programme
	case DisplayConfiguration:
#ifdef DEBUG
		debug("[Display] configuration screen");
#endif
		display.showPage(PageConfiguration);
		programStatus = EntryConfiguration;
		timeout = 0;
#ifdef DEBUG
		debug("[State] configuration input");
#endif
		break;

	// les saisies de l'écran de config
	case EntryConfiguration:
		// choix non fait, on abandonne le début du jeu
		// et on ré-affiche la page d'accueil
		if (timeout > SECONDS_TO_ANSWER)
		{
#ifdef DEBUG
			debug("[State] time out!");
#endif
			programStatus = DisplayWelcome;
			break;
		}
		// touche annulation pressée
		if (display.isCancel())
		{
			programStatus = DisplayWelcome;
			break;
		}
		break;

	// quelqu'un est là, on affiche le choix du niveau
	case DisplayChooseLevel:
#ifdef DEBUG
		debug("[Display] choose start level screen");
#endif
		display.showPage(PageChoixNiveau);
		programStatus = WaitForLevel;
		timeout = 0;
#ifdef DEBUG
		debug("[State] start level input");
#endif
		break;

	// attente du choix de niveau
	case WaitForLevel:
		// choix non fait, on abandonne le début du jeu
		// et on ré-affiche la page d'accueil
		if (timeout > SECONDS_TO_ANSWER)
		{
#ifdef DEBUG
			debug("[State] time out!");
#endif
			programStatus = DisplayWelcome;
			break;
		}
		// touche annulation pressée
		if (display.isCancel())
		{
#ifdef DEBUG
			debug("[State] cancel");
#endif
			programStatus = DisplayWelcome;
			break;
		}
		// le joueur a-t'il choisit son niveau de difficulté ?
		playerLevel = display.getLevel();
		// oui !
		if (playerLevel > 0)
		{
			// on lance le jeu
			programStatus = InitNewGame;
			break;
		}
		break;

	// le choix du niveau est fait
	// on affiche l'écran des questions
	case InitNewGame:
#ifdef DEBUG
		debug("[State] starting a new game");
#endif
		// initialisation d'un nouveau jeu
		game.startNewGame(playerLevel, MAX_QUESTIONS_PER_GAME);
		// on affiche la page des questions
#ifdef DEBUG
		debug("[Display] question screen");
#endif
		display.showPage(PageQuestion);
		// on demande l'affichage de la 1ère question
		programStatus = DisplayQuestion;
		break;

	// on affiche une question
	case DisplayQuestion:
#ifdef DEBUG
		debug("[Display] question");
#endif
		// affichage de la question en cours
		display.showQuestion(game.getCurrentQuestionNumber(), game.getCurrentQuestionLevel(), game.getCurrentCategory(), game.getCurrentQuestion(),
							 game.getCurrentAnswer1(), game.getCurrentAnswer2(), game.getCurrentAnswer3());
		// et on va attendre la réponse du joueur
		programStatus = WaitForAnswer;
		timeout = 0;
#ifdef DEBUG
		debug("[State] answer input");
#endif
		break;

	// on attend la réponse du joueur
	case WaitForAnswer:
		// il n'a pas répondu dans les temps
		// le jeu est terminé !
		if (timeout > SECONDS_TO_ANSWER)
		{
#ifdef DEBUG
			debug("[State] time out!");
#endif
			programStatus = DisplaySorry;
			break;
		}
		// touche annulation pressée, il abandonne le jeu
		if (display.isCancel())
		{
#ifdef DEBUG
			debug("[State] cancel");
#endif
			programStatus = DisplayWelcome;
			break;
		}
		// le joueur a-t'il donné une réponse ?
		playerAnswer = display.getAnswer();
		// oui :)
		if (playerAnswer > 0)
		{
			// on joue sa réponse
			game.playAnswer(playerAnswer);
			// on passe à la question suivante
			game.nextQuestion();
			// est-ce la fin du jeu ?
			if (game.isGameFinish())
			{
				// oui, on affiche le résultat
				programStatus = DisplayResult;
				break;
			}
			// non ce n'est pas terminé, on affiche la nouvelle question
			programStatus = DisplayQuestion;
			break;
		}
		display.displayChrono(uint8_t(timeout / 1000));
		break;

	// le joueur n'a pas répondu
	// on lui affiche qu'il a perdu / abandonner
	case DisplaySorry:
#ifdef DEBUG
		debug("[Display] leave screen");
#endif
		// affichage de la page d'abandon
		display.showPage(PageAbandon);
		// avec un délai plus court
		timeout = 2 * SECONDS_TO_ANSWER / 3;
		programStatus = WaitForEnding;
#ifdef DEBUG
		debug("[State] keypress input");
#endif
		break;

	// le joueur a répondu à toutes les questions
	// on affiche le résultat
	case DisplayResult:
#ifdef DEBUG
		debug("[Display] result screen");
#endif
		// on affiche la page de résultat
		display.showPage(PageResultat);
		// et on affiche le résultat du joueur
		display.showResult(game.getNumberOfGoodAnswers(), game.getNumberOfBadAnswers(), game.getPlayerStatus(), game.getPlayerMotto());
		programStatus = WaitForEnding;
		timeout = 0;
#ifdef DEBUG
		debug("[State] keypress input");
#endif
		break;

	// on attend l'appui sur une touche
	// ou le timeout
	// pour retourner à l'accueil
	case WaitForEnding:
		if (timeout > SECONDS_TO_ANSWER)
		{
#ifdef DEBUG
			debug("[State] time out!");
#endif
			programStatus = DisplayWelcome;
			break;
		}
		if (display.isKeyPress())
		{
			programStatus = DisplayWelcome;
			break;
		}
		break;
	}
}