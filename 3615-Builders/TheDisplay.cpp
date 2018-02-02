#include "TheDisplay.hpp"

Minitel minitel(PIN_MINITEL_SERIAL_TX, PIN_MINITEL_SERIAL_RX);

void TheDisplay::setup()
{
	minitel.clearScreen();
	minitel.graphicMode();
	minitel.noPixelate();
	minitel.textMode();
	minitelTimeLastCommand = 0;
	keyIsPressed = false;
}

void TheDisplay::loop()
{
	if (minitelTimeLastCommand > MINITEL_SCREEN_TIMEOUT)
	{
		minitel.moveCursorTo(0, 0);
		Serial.println(F("Ping minitel"));
		minitelTimeLastCommand = 0;
	}
	minitel.readKey();
	if (minitel.isCharacterKey())
	{
		keyIsPressed = true;
		//process();
	}
}

void TheDisplay::sendBytes(uint16_t size, const uint8_t bytes[])
{
	for (uint16_t i = 0; i < size; i++)
	{
		uint8_t c = bytes[i];
		minitel.textByte(c);
	}
	minitelTimeLastCommand = 0;
}

void TheDisplay::showPage(MINITEL_PAGE page)
{
	// TODO: intégrer les pages manquantes
	switch(page)
	{
		case PageConfiguration:
			sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageAccueil:
			sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageChoixNiveau:
			sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageQuestion:
			sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageAbandon:
			sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageResultat:
			sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
	}
}
void TheDisplay::showQuestion(uint8_t number, String category, String question, String answer1, String answer2, String answer3)
{
	// TODO: afficher la question
}

bool TheDisplay::isKeyPress()
{
	bool res = keyIsPressed;
	keyIsPressed = false;
	return res;
}

bool TheDisplay::isCancel()
{
	// TODO: test si la touche annulation a été pressée
	return false;
}

uint8_t TheDisplay::getLevel()
{
	// TODO: renvoyer de 1 à 5 si le joueur a choisit
	return 0;
}

uint8_t TheDisplay::getAnswer()
{
	// TODO: renvoyer 1, 2 ou 3 si le joueur a choisit
	return 0;
}

void TheDisplay::showResult(uint8_t goodAnswers, uint8_t badAnswers, PlayerStatus status, String moto)
{
	// TODO: afficher le résultat
}
