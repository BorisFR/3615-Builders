#include <Arduino.h>
#include <TimeLib.h>
#include "ElapsedMillis.hpp"
#include "MyConfig.hpp"
#include "Game.hpp"
#include "TheDisplay.hpp"
#include "TheData.hpp"

// ce qui gère le QCM
Game game;
// ce qui gère le lien avec le Minitel (écran + clavier)
TheDisplay display;

TheData theData;
// pour gérer les différents time out pendant le jeu
ElapsedMillis timeout;

String gamerName;
uint8_t playerAnswer;
uint8_t playerLevel;

bool showScores;
String inputSecret;
String secretCode = SECRETCODE;
bool showQRcode = true; 
uint8_t showQRcodeFor = MAX_PODIUM_PLAYER;
uint8_t midi = 13;

// les différents états du programme
///////////////////////////////////////////////////////////////////////////////
enum ProgramStatus
{
	DisplayConfiguration,
	EntryConfiguration,
	DisplayHallOfFame,
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
	WaitForQRcode,
	DisplayQRcode,
	WaitForEnding,
	DisplaySorry
} programStatus;

#ifdef DEBUG
void debug(String text)
{
	Serial.println(text);
}
#endif

time_t getTeensy3Time()
{
	return Teensy3Clock.get();
}

void printDigits(int digits)
{
	// utility function for digital clock display: prints preceding colon and leading 0
	Serial.print(":");
	if (digits < 10)
		Serial.print('0');
	Serial.print(digits);
}

void digitalClockDisplay()
{
	// digital clock display of the time
	Serial.print(hour());
	printDigits(minute());
	printDigits(second());
	Serial.print(" ");
	Serial.print(day());
	Serial.print(" ");
	Serial.print(month());
	Serial.print(" ");
	Serial.print(year());
	Serial.println();
}

// initialisation globale du programme
///////////////////////////////////////////////////////////////////////////////
void setup()
{
#ifdef DEBUG
	setSyncProvider(getTeensy3Time);
	Serial.begin(115200);
	debug("3615 Builders starting...");
#endif
	digitalClockDisplay();
	theData.setup();
	game.setup();
	display.setup();
	if (theData.hiscoresPoints[0] > 0)
	{
		for (uint8_t i = 0; i < MAX_SCORES; i++)
		{
			display.setHiScore(i, theData.hiscoresName[i], theData.hiscoresPoints[i]);
		}
	}
	display.setQRcodeDisplay(showQRcode);
	display.setPlayerPodium(showQRcodeFor);
	display.setMidi(midi);
	showScores = false;
	programStatus = DisplayWelcome;

	//theData.saveScore("Stéphane", 326);
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
	// on affiche la tableau des scores
	///////////////////////////////////////////////////////////////////////////
	case DisplayHallOfFame:
		display.showPage(PageScores);
		showScores = true;
		programStatus = WaitForKeypress;
		timeout = 0;
		display.clearKeyboard();
		inputSecret = "";
		break;

	// on affiche la page d'accueil
	///////////////////////////////////////////////////////////////////////////
	case DisplayWelcome:
		showScores = false;
		display.showPage(PageAccueil);
		programStatus = WaitForKeypress;
		//display.showPage(PageResultat);
		//display.showResult(20, 0, GrandMaitre, MASTER_MOTTO, 142);
		//display.showResult(18, 2, Chevalier, CHEVALIER_MOTTO, 99);
		//display.showResult(10, 9, Padawan, PADAWAN_MOTTO);
		//display.showResult(9, 10, Initie, INITIE_MOTTO);
		//display.showResult(1, 19, Sensitif, SENSITIF_MOTTO);
		//display.showResult(0, 20, Human, HUMAN_MOTTO);
		//programStatus = WaitForEnding;
		timeout = 0;
		display.clearKeyboard();
		inputSecret = "";
		break;

	// attente que quelqu'un se manifeste...
	case WaitForKeypress:
		// personne n'interagit
		if ((timeout > SECONDS_TO_ANSWER) || (display.isCancel()))
		{
			// juste ré-affiche la page
			// on peut imaginer faire des animations...
			if(showScores)
				programStatus = DisplayWelcome;
			else
				programStatus = DisplayHallOfFame;
			showScores = !showScores;
			break;
		}
		// TODO: gérer le code secret pour l'écran de configuration
		if (display.isKeyPress())
		{
			char c = display.getTextKey();
			inputSecret += c;
			Serial.print(c);
			if(inputSecret == secretCode.substring(0, inputSecret.length()))
			{
				Serial.print(".");
				if(inputSecret.length() == secretCode.length())
				{
					display.clearKeyboard();
					programStatus = DisplayConfiguration;
					break;
				}
				break;
			}
			display.clearKeyboard();
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
		display.clearKeyboard();
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
			display.clearKeyboard();
			programStatus = DisplayWelcome;
			break;
		}
		if (display.isKeyPress())
		{
			char c = display.getTextKey();
			switch(c)
			{
				case 'c':
					display.clearHiScores();
					display.bip();
					break;
				case 'l':
					theData.loadScores();
					for(uint8_t i = 0; i < MAX_SCORES; i++)
					{
						display.setHiScore(i, theData.hiscoresName[i], theData.hiscoresPoints[i]);
					}
					break;
				case 'a':
					theData.loadScoresAM(midi);
					for (uint8_t i = 0; i < MAX_SCORES; i++)
					{
						display.setHiScore(i, theData.hiscoresName[i], theData.hiscoresPoints[i]);
					}
					break;
				case 'p':
					theData.loadScoresPM(midi);
					for (uint8_t i = 0; i < MAX_SCORES; i++)
					{
						display.setHiScore(i, theData.hiscoresName[i], theData.hiscoresPoints[i]);
					}
					break;
				case 'h':
					midi++;
					if(midi > 14)
						midi = 11;
					display.setMidi(midi);
					display.clearKeyboard();
					programStatus = DisplayConfiguration;
					break;
				case 'q':
					showQRcode = !showQRcode;
					display.setQRcodeDisplay(showQRcode);
					display.clearKeyboard();
					programStatus = DisplayConfiguration;
					break;
				case 'j':
					showQRcodeFor++;
					if(showQRcodeFor > MAX_PODIUM_PLAYER)
						showQRcodeFor = 1;
					display.setPlayerPodium(showQRcodeFor);
					display.clearKeyboard();
					programStatus = DisplayConfiguration;
					break;
				case 0x0d:
					display.clearKeyboard();
					programStatus = DisplayWelcome;
					break;
			}
			display.clearKeyboard();
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
		display.clearKeyboard();
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
			display.clearKeyboard();
			gamerName = display.getInputValue();
			programStatus = DisplayChooseLevel;
			break;
		}
		if(display.displayChrono(uint8_t(timeout / 1000)))
			timeout = 0;
		// touche annulation pressée
		if (display.isCancel())
		{
			display.clearKeyboard();
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
		display.clearKeyboard();
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
			display.clearKeyboard();
			programStatus = DisplayWelcome;
			break;
		}
		// le joueur a-t'il choisit son niveau de difficulté ?
		playerLevel = display.getLevel();
		// oui !
		if (playerLevel > 0)
		{
			display.clearKeyboard();
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
		display.clearKeyboard();
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
			display.clearKeyboard();
			programStatus = DisplayWelcome;
			break;
		}
		// le joueur a-t'il donné une réponse ?
		playerAnswer = display.getAnswer();
		// oui :)
		if (playerAnswer > 0)
		{
			display.clearKeyboard();
			// on joue sa réponse
			game.playAnswer(playerAnswer);
			#ifdef DEBUG
			if(game.isAnswerGood())
			{
				debug("Good answer");
			} else {
				debug("False answer");
				display.bip();
			}
			#endif
			// est-ce la fin du jeu ?
			if (game.isGameFinish())
			{
				// oui, on affiche le résultat
				programStatus = DisplayResult;
				break;
			}
			// on passe à la question suivante
			game.nextQuestion();
			// on affiche la nouvelle question
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
		display.clearKeyboard();
		break;

	// le joueur a répondu à toutes les questions
	// on affiche le résultat
	///////////////////////////////////////////////////////////////////////////
	case DisplayResult:
		Serial.println("page result");
		// on affiche la page de résultat
		display.showPage(PageResultat);
		// on sauvegarde le résultat du joueur
		theData.saveScore(gamerName, game.getPoints(), game.questionsID, game.answerinGame);
		// et on affiche le résultat du joueur
		display.showResult(gamerName, game.getNumberOfGoodAnswers(),
						   game.getNumberOfBadAnswers(), game.getPlayerStatus(),
						   game.getPlayerMotto(), game.getPoints());
	   if(display.onPodium())
			programStatus = WaitForQRcode;
		else
			programStatus = WaitForEnding;
		timeout = 0;
		display.clearKeyboard();
		break;

	// on attend l'appui sur une touche
	// ou le timeout
	// pour afficher le QR code
	///////////////////////////////////////////////////////////////////////////
	case WaitForQRcode:
		if (timeout > SECONDS_TO_ANSWER)
		{
			programStatus = DisplayQRcode;
			break;
		}
		if (display.isCancel())
		{
			display.clearKeyboard();
			programStatus = DisplayQRcode;
			break;
		}
		if (display.isKeyPress())
		{
			display.clearKeyboard();
			timeout = 0;
			break;
		}
		break;

	// on affiche le QRcode
	///////////////////////////////////////////////////////////////////////////
	case DisplayQRcode:
		display.showPage(PageQRcode);
		programStatus = WaitForEnding;
		timeout = 0;
		display.clearKeyboard();
		break;

	// on attend l'appui sur une touche
	// ou le timeout
	// pour retourner à l'accueil
	///////////////////////////////////////////////////////////////////////////
	case WaitForEnding:
		if (timeout > SECONDS_TO_ANSWER)
		{
			programStatus = DisplayHallOfFame;
			break;
		}
		if (display.isCancel())
		{
			display.clearKeyboard();
			programStatus = DisplayHallOfFame;
			break;
		}
		if (display.isKeyPress())
		{
			display.clearKeyboard();
			timeout = 0;
			break;
		}
		break;
	}
}