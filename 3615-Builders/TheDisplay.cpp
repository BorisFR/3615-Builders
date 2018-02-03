#include "TheDisplay.hpp"

//Minitel minitel(PIN_MINITEL_SERIAL_TX, PIN_MINITEL_SERIAL_RX);
Minitel minitel(SERIAL_MINITEL);

void TheDisplay::setup()
{
	int speed = minitel.searchSpeed();
	Serial.println(speed);
	minitel.newScreen();
	minitel.smallMode();
	minitel.print("Hello world!");

	/*minitel.clearScreen();
	minitel.graphicMode();
	minitel.noPixelate();
	minitel.textMode();*/
	minitelTimeLastCommand = 0;
	keyIsPressed = false;
	lastKey = 0;
}

bool TheDisplay::isTextKey(unsigned long key)
{
	if ((key != 0) &&
		(key != CONNEXION_FIN) &&
		(key != SOMMAIRE) &&
		(key != ANNULATION) &&
		(key != RETOUR) &&
		(key != REPETITION) &&
		(key != GUIDE) &&
		(key != CORRECTION) &&
		(key != SUITE) &&
		(key != ENVOI))
	{
		return true;
	}
	return false;
}

void TheDisplay::loop()
{
	if (minitelTimeLastCommand > MINITEL_SCREEN_TIMEOUT)
	{
		minitel.moveCursorXY(0, 0);
		//minitel.moveCursorTo(0, 0);
		Serial.println(F("Ping minitel"));
		minitelTimeLastCommand = 0;
	}
	lastKey = minitel.getKeyCode();
	//minitel.readKey();
	if (isTextKey(lastKey)) //(minitel.isCharacterKey())
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
		minitel.writeByte(c);
		//minitel.textByte(c);
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
			minitel.newScreen();
			minitel.print("Accueil - appuyez sur une touche");
			//sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageChoixNiveau:
			minitel.newScreen();
			minitel.print("Niveau - choisir de 1 à 5");
			//sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageQuestion:
			minitel.newScreen();
			minitel.print("Réponse - choisir de 1, 2 ou 3");
			//sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageAbandon:
			minitel.newScreen();
			minitel.print("Abandon");
			//sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageResultat:
			minitel.newScreen();
			minitel.print("Résultat");
			//sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
	}
}
void TheDisplay::showQuestion(uint8_t number, String category, String question, String answer1, String answer2, String answer3)
{
	// TODO: afficher la question
	minitel.println();
	minitel.println("Question " + String(number) + " / " + String(20));
	minitel.println("Catégorie : " + category);
	minitel.println(question);
	minitel.println("1 : " + answer1);
	minitel.println("2 : " + answer2);
	minitel.println("3 : " + answer3);
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

uint8_t TheDisplay::getNumericInputNumber(uint8_t from, uint8_t to)
{
	if ((lastKey >= (uint8_t)(from + 48)) && (lastKey <= (uint8_t)(to + 48)))
	{
		uint8_t value = lastKey - 48;
		lastKey = 0;
		keyIsPressed = false;
		return value;
	}
	return 0;
}

uint8_t TheDisplay::getLevel()
{
	return getNumericInputNumber(1, 5); //NUMBER_QCM_LEVEL);
}

uint8_t TheDisplay::getAnswer()
{
	return getNumericInputNumber(1, 3);
}

void TheDisplay::showResult(uint8_t goodAnswers, uint8_t badAnswers, PlayerStatus status, String motto)
{
	minitel.println();
	minitel.println("Résultat " + String(goodAnswers) + " / " + String(badAnswers));
	minitel.println(motto);
}
