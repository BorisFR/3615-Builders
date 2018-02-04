#include <Arduino.h>
#include "ElapsedMillis.hpp"
#include "MyConfig.hpp"
#include "Game.hpp"
#include "TheDisplay.hpp"

// ce qui gère le QCM
Game game;
// ce qui gère le lien avec le Minitel (écran + clavier)
TheDisplay display;
// pour gérer les différents time out pendant le jeu
ElapsedMillis timeout;

String gamerName;
uint8_t playerAnswer;
uint8_t playerLevel;

// les différents états du programme
///////////////////////////////////////////////////////////////////////////////
enum ProgramStatus
{
	DisplayConfiguration,
	EntryConfiguration,
	DisplayWelcome,
	WaitForKeypress,
	DisplayChooseLevel,
	WaitForLevel,
	DisplayEnterName,
	WaitForName,
	InitNewGame,
	DisplayQuestion,
	WaitForAnswer,
	DisplayResult,
	WaitForEnding,
	DisplaySorry
} programStatus;

#ifdef DEBUG
void debug(String text)
{
	Serial.println(text);
}
#endif

// initialisation globale du programme
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
void loop()
{
	game.loop();
	display.loop();

	// le boulot à faire en fonction de l'état en cours
	switch (programStatus)
	{
	// on affiche la page d'accueil
	///////////////////////////////////////////////////////////////////////////
	case DisplayWelcome:
		display.showPage(PageAccueil);
		//display.showPage(PageResultat);
		//display.showResult(20, 0, GrandMaitre, MASTER_MOTTO);
		//display.showResult(18, 2, Chevalier, CHEVALIER_MOTTO);
		//display.showResult(10, 9, Padawan, PADAWAN_MOTTO);
		//display.showResult(9, 10, Initie, INITIE_MOTTO);
		//display.showResult(1, 19, Sensitif, SENSITIF_MOTTO);
		//display.showResult(0, 20, Human, HUMAN_MOTTO);
		programStatus = WaitForKeypress;
		timeout = 0;
		break;

	// attente que quelqu'un se manifeste...
	case WaitForKeypress:
		// personne n'interagit
		if (timeout > SECONDS_TO_ANSWER)
		{
			// juste ré-affiche la page
			// on peut imaginer faire des animations...
			programStatus = DisplayWelcome;
			break;
		}
		if(display.isCancel())
		{
			programStatus = DisplayEnterName;
			break;
		}
		// TODO: gérer le code secret pour l'écran de configuration
		if (display.isKeyPress())
		{
			programStatus = DisplayEnterName;
			break;
		}
		break;

	// on affiche la page de configuration du programme
	///////////////////////////////////////////////////////////////////////////
	case DisplayConfiguration:
		display.showPage(PageConfiguration);
		programStatus = EntryConfiguration;
		timeout = 0;
		break;

	// les saisies de l'écran de config
	case EntryConfiguration:
		// choix non fait, on abandonne le début du jeu
		// et on ré-affiche la page d'accueil
		if (timeout > SECONDS_TO_ANSWER)
		{
			programStatus = DisplayWelcome;
			break;
		}
		// touche annulation pressée
		if (display.isCancel())
		{
			programStatus = DisplayWelcome;
			break;
		}
		display.displayChrono(uint8_t(timeout / 1000));
		break;

	// saisie du nom du joueur
	///////////////////////////////////////////////////////////////////////////
	case DisplayEnterName:
		display.showPage(PageSaisieNom);
		programStatus = WaitForName;
		timeout = 0;
		break;

	// les saisies de l'écran de config
	case WaitForName:
		if (timeout > SECONDS_TO_ANSWER)
		{
			programStatus = DisplayWelcome;
			break;
		}
		if(display.isInputReady())
		{
			gamerName = display.getInputValue();
			programStatus = DisplayChooseLevel;
			break;
		}
		if(display.displayChrono(uint8_t(timeout / 1000)))
			timeout = 0;
		// touche annulation pressée
		if (display.isCancel())
		{
			programStatus = DisplayWelcome;
			break;
		}
		break;

	// Choix du niveau
	///////////////////////////////////////////////////////////////////////////
	case DisplayChooseLevel:
		display.showPage(PageChoixNiveau);
		programStatus = WaitForLevel;
		timeout = 0;
		break;

	// attente du choix de niveau
	case WaitForLevel:
		// choix non fait, on abandonne le début du jeu
		// et on ré-affiche la page d'accueil
		if (timeout > SECONDS_TO_ANSWER)
		{
			programStatus = DisplayWelcome;
			break;
		}
		// touche annulation pressée
		if (display.isCancel())
		{
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
		if (display.displayChrono(uint8_t(timeout / 1000)))
			timeout = 0;
		break;

	// on démarre le jeu
	///////////////////////////////////////////////////////////////////////////
	case InitNewGame:
		// initialisation d'un nouveau jeu
		game.startNewGame(playerLevel, MAX_QUESTIONS_PER_GAME);
		// on affiche la page des questions
		display.showPage(PageQuestion);
		// on demande l'affichage de la 1ère question
		programStatus = DisplayQuestion;
		break;

	// on affiche une question
	//////////////////////////
	case DisplayQuestion:
		// affichage de la question en cours
		display.showQuestion(game.getCurrentQuestionNumber(), 
			game.getCurrentQuestionLevel(), game.getCurrentCategory(), 
			game.getCurrentQuestion(), game.getCurrentAnswer1(), 
			game.getCurrentAnswer2(), game.getCurrentAnswer3());
		// et on va attendre la réponse du joueur
		programStatus = WaitForAnswer;
		timeout = 0;
		break;

	// on attend la réponse du joueur
	/////////////////////////////////
	case WaitForAnswer:
		// il n'a pas répondu dans les temps
		// le jeu est terminé !
		if (timeout > SECONDS_TO_ANSWER)
		{
			programStatus = DisplaySorry;
			break;
		}
		// touche annulation pressée, il abandonne le jeu
		if (display.isCancel())
		{
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
			#ifdef DEBUG
			if(game.isAnswerGood())
			{
				debug("Good answer");
			} else {
				debug("False answer");
			}
			#endif
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
	///////////////////////////////////////////////////////////////////////////
	case DisplaySorry:
		// affichage de la page d'abandon
		display.showPage(PageAbandon);
		// avec un délai plus court
		timeout = 2 * SECONDS_TO_ANSWER / 3;
		programStatus = WaitForEnding;
		break;

	// le joueur a répondu à toutes les questions
	// on affiche le résultat
	///////////////////////////////////////////////////////////////////////////
	case DisplayResult:
		// on affiche la page de résultat
		display.showPage(PageResultat);
		// et on affiche le résultat du joueur
		display.showResult(game.getNumberOfGoodAnswers(), 
			game.getNumberOfBadAnswers(), game.getPlayerStatus(), 
			game.getPlayerMotto());
		programStatus = WaitForEnding;
		timeout = 0;
		break;

	// on attend l'appui sur une touche
	// ou le timeout
	// pour retourner à l'accueil
	///////////////////////////////////////////////////////////////////////////
	case WaitForEnding:
		if (timeout > SECONDS_TO_ANSWER)
		{
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