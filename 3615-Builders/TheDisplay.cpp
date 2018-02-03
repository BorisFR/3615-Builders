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
			sendBytes(PAGE_ACCUEIL_SIZE, page_accueil);
			/*minitel.newScreen();
			minitel.print("Test");
			minitel.printInBox("Bonjour le monde test", 1, 1, 9, 3, CARACTERE_BLANC);
			minitel.printInBox("Bonjour le monde test", 1, 4, 10, 3, CARACTERE_BLANC);
			minitel.printInBox("Bonjour le monde test", 1, 7, 11, 3, CARACTERE_BLANC);
			minitel.printInBox("Bonjour le monde test", 1, 10, 15, 3, CARACTERE_BLANC);
			minitel.printInBox("Bonjour le monde test", 1, 13, 16, 3, CARACTERE_BLANC);
			minitel.printInBox("Bonjour le monde test", 1, 16, 17, 3, CARACTERE_BLANC);*/
			break;
		case PageChoixNiveau:
			sendBytes(PAGE_DIFFICULTE_SIZE, page_difficulte);
			break;
		case PageQuestion:
			sendBytes(PAGE_QUESTION_SIZE, page_question);
			break;
		case PageAbandon:
			minitel.newScreen();
			minitel.print("Abandon");
			//sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageResultat:
			sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
	}
}

void TheDisplay::writeTextOn(String text, uint8_t width)
{
	minitel.print(text);
	// et on efface le restant de la ligne
	for(uint8_t i = text.length(); i < width; i++)
		minitel.print(" ");
}

void TheDisplay::writeTextInBox(String chaine, uint8_t x, uint8_t y, uint8_t width, uint8_t height, byte color)
{
	uint8_t startX = x;
	uint8_t startY = y;
	// on efface la zone
	for (uint8_t j = startY; j < (startY + height); j++)
	{
		minitel.moveCursorXY(startX, j);
		for (uint8_t i = startX; i < (startX + width); i++)
		{
			minitel.printChar(32);
		}
	}
	uint8_t currentY = y;
	String text = chaine.trim();
	// compteur du reste à écrire
	uint8_t lengthToPut = text.length();
	// position de ce qui reste à écrire
	//Serial.println();
	while (lengthToPut > 0)
	{
		uint8_t currentPosText = 0;
		//Serial.println("Pos:" + String(currentPosText) + " Restant: " + String(lengthToPut) + " à mettre: " + String(width) + " =>*" + text + "*");
		// on calcule ce qu'il faut écrire
		int8_t lengthToGet = width; // 9
		// si c'est trop, on prend vraiment que le reste à
		if (lengthToGet > lengthToPut)
			lengthToGet = lengthToPut;
		// on extrait la chaine à écrire
		String temp = text.substring(currentPosText, currentPosText + lengthToGet);
		//Serial.print("chaine=*" + temp + "*");
		// coupe-t'on un mot ?
		if ((currentPosText + lengthToGet) < lengthToPut)
		{ // plus rien après
			// si dernier char ou prochain char n'est pas espace
			int8_t lastPos = temp.lastIndexOf(' ');
			//Serial.print(" last:" + String(lastPos) + " toget:" + String(lengthToGet));
			if ((lastPos + 1) != lengthToGet) // dernier n'est pas ' '
			{
				//Serial.print(" =*" + text.substring(lengthToGet, lengthToGet + 1) + "*");
				if (text.substring(lengthToGet, lengthToGet + 1) != ' ') // prochaine n'est pas ' '
				{
					//Serial.print(" *");
					lengthToGet = lastPos;
					temp = text.substring(currentPosText, currentPosText + lengthToGet);
				}
			}
		}
		//Serial.println(" Ecrit: " + String(lengthToGet) + " =>*" + temp + "*");
		minitel.moveCursorXY(x, currentY++);
		minitel.attributs(CARACTERE_BLANC);
		minitel.print(temp.trim());
		currentPosText += lengthToGet;
		text = text.substring(currentPosText).trim();
		lengthToPut = text.length();
	}
}

void TheDisplay::displayChrono(uint8_t value)
{
	if (value == memoChrono)
		return;
	minitel.noCursor();
	memoChrono = value;
	// chrono (bleu)
	minitel.moveCursorXY(39, 24);
	minitel.print(String(30 - value));
	if(value == 21)
		minitel.print(" ");
	// wait
	minitel.moveCursorXY(17, 24);
	minitel.cursor();
}

void TheDisplay::showQuestion(uint8_t number, uint8_t level, String category, String question, String answer1, String answer2, String answer3)
{
	minitel.noCursor();
	// niveau (vert)
	minitel.moveCursorXY(8, 4);
	minitel.attributs(CARACTERE_VERT);
	minitel.print(String(level));
	// n° question (vert)
	if (number < 10) {
		minitel.moveCursorXY(35, 4);
	}
	else
	{
		minitel.moveCursorXY(34, 4);
	}
	minitel.attributs(CARACTERE_VERT);
	minitel.print("n");
	minitel.printSpecialChar(DEGRE);
	minitel.print(String(number) + "/" + String(MAX_QUESTIONS_PER_GAME));
	// catégorie (bleu sur jaune)
	minitel.moveCursorXY(12, 6);
	minitel.attributs(CARACTERE_BLEU);
	minitel.attributs(FOND_JAUNE);
	writeTextOn(category, 28);
	// question
	//writeTextInBox(question, 3, 8, 36, 10);
	writeTextInBox(question, 3, 8, 36, 4, CARACTERE_BLANC);
	// réponse 1
	writeTextInBox(answer1, 4, 15, 36, 3, CARACTERE_BLANC);
	// réponse 2
	writeTextInBox(answer2, 4, 18, 36, 3, CARACTERE_BLANC);
	// réponse 3
	writeTextInBox(answer3, 4, 21, 36, 3, CARACTERE_BLANC);
	// chrono (bleu)
	minitel.moveCursorXY(39, 24);
	minitel.print("30");
	memoChrono = 30;
	// wait
	minitel.moveCursorXY(17, 24);
	minitel.cursor();
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
