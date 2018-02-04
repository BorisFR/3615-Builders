#include "TheDisplay.hpp"

Minitel minitel(SERIAL_MINITEL);

void TheDisplay::setup()
{
	int speed = minitel.searchSpeed();
	Serial.println("Communication : " + String(speed) + " bauds");
	minitel.newScreen();
	minitel.smallMode();
	minitel.print("Bonjour le monde !");
	//minitelTimeLastCommand = 0;
	isInInputTextMode = false;
	keyIsPressed = false;
	lastKey = 0;
	for (uint8_t i = 0; i < MAX_SCORES; i++)
	{
		scores[i] = 0; //MAX_SCORES - i;
		gamertag[i] = " ";
	}
	gamertag[0] = " R2 Builders ";
	gamertag[1] = "*************";
	gamertag[2] = "  Le Q.C.M. ";
	gamertag[3] = "  Star Wars ";
	gamertag[4] = "";
	gamertag[5] = "Made by";
	gamertag[6] = "       Boris ";
	gamertag[7] = " - 02/2018 - ";
	gamertag[8] = "";
	gamertag[9] = "Just in time";
	gamertag[10] = "    for";
	gamertag[11] = "* M A K E R";
	gamertag[12] = "  F A I R E *";
	gamertag[13] = "";
	gamertag[14] = " -- Lille -- ";
	gamertag[15] = "";
	gamertag[16] = "";
	gamertag[17] = "";
	gamertag[18] = "";
	gamertag[19] = "";
	theInput = "*** Boris ***";
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
		(key != SUITE))
	{
		return true;
	}
	return false;
}

bool TheDisplay::displayChrono(uint8_t value)
{
	if (value == memoChrono)
		return false;
	minitel.noCursor();
	memoChrono = value;
	// chrono (bleu)
	minitel.moveCursorXY(39, 24);
	minitel.print(String(30 - value));
	if (value == 21)
		minitel.print(" ");
	// wait
	minitel.moveCursorXY(posX, posY);
	minitel.cursor();
	if (resetTimer){
		resetTimer = false;
		return true;
	}
	return false;
}

void TheDisplay::startInput(uint8_t size)
{
	maxInputSize = size;
	theInput = "";
	inputIsReady = false;
	isInInputTextMode = true;
}

String TheDisplay::getInputValue()
{
	return theInput;
}

bool TheDisplay::isInputReady()
{
	return inputIsReady;
}

void TheDisplay::loop()
{
/*	if (minitelTimeLastCommand > MINITEL_SCREEN_TIMEOUT)
	{
		minitel.moveCursorXY(0, 0);
		Serial.println(F("Ping minitel"));
		minitelTimeLastCommand = 0;
	}*/
	lastKey = minitel.getKeyCode();
	if (isTextKey(lastKey))
	{
		keyIsPressed = true;
	}
	// à mettre en dernier !
	// attente de la saisie d'un texte ?
	if (!isInInputTextMode)
		return;
	keyIsPressed = false;
	// une touche appuyée ?
	if (lastKey == 0) 
		return;
	if (inputIsReady)
		return;
	if (lastKey == ENVOI)
	{
		// aucune saisie en cours, on ne fait rien
		if (theInput.length() == 0)
			return;
		resetTimer = true;
		inputIsReady = true;
		return;
	}
	// on delete le dernier caractère
	if (lastKey == CORRECTION)
	{
		resetTimer = true;
		// aucune saisie en cours, on ne fait rien
		if (theInput.length() == 0)
			return;
		if (theInput.length() == 1)
			theInput = "";
		else
			theInput = theInput.substring(0, theInput.length() - 1);
		posX--;
		minitel.noCursor();
		minitel.moveCursorXY(posX - theInput.length(), posY);
		minitel.print(theInput);
		for (uint8_t i = theInput.length(); i < maxInputSize; i++)
			minitel.print(".");
		minitel.moveCursorXY(posX, posY);
		minitel.cursor();
		return;
	}
	// ajout du caractère saisie
	if (lastKey >= 32 && lastKey <= 126)
	{
		resetTimer = true;
		if (theInput.length() >= maxInputSize)
			return;
		char x = ' ' + (lastKey - 32);
		theInput += String(x);
		minitel.print(x);
		posX++;
		return;
	}
}

void TheDisplay::sendBytes(uint16_t size, const uint8_t bytes[])
{
	minitel.noCursor();
	for (uint16_t i = 0; i < size; i++)
	{
		uint8_t c = bytes[i];
		minitel.writeByte(c);
	}
	//minitelTimeLastCommand = 0;
}

void TheDisplay::showPage(MINITEL_PAGE page)
{
	isInInputTextMode = false;
	// TODO: intégrer les pages manquantes
	switch(page)
	{
		case PageConfiguration:
			sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			break;
		case PageScores:
			sendBytes(90, page_header); // on enleve le cadre
			sendBytes(HALL_OF_FAME_SIZE, hall_of_fame);
			minitel.textMode();
			for (uint8_t i = 0; i < (MAX_SCORES / 2); i++)
			{
				minitel.moveCursorXY(0, 6 + i * 2);
				minitel.attributs(DOUBLE_HAUTEUR);
				minitel.attributs(CARACTERE_VERT);
				minitel.attributs(INVERSION_FOND);
				minitel.print(String(i + 1));
				minitel.attributs(FOND_NORMAL);
				minitel.print(" ");
				minitel.attributs(CARACTERE_CYAN);
				if (scoreToHighlight == i)
					minitel.attributs(CLIGNOTEMENT);
				minitel.print(gamertag[i]);
				minitel.moveCursorXY(1 + 1 + 13 + 1, 7 + i * 2);
				minitel.attributs(CARACTERE_MAGENTA);
				if (scoreToHighlight == i)
					minitel.attributs(CLIGNOTEMENT);
				writeTextRight(String(scores[i]), 3);
				if (scoreToHighlight == i)
					minitel.attributs(FIXE);

				minitel.moveCursorXY(20, 6 + i * 2);
				minitel.attributs(DOUBLE_HAUTEUR);
				minitel.attributs(CARACTERE_VERT);
				minitel.attributs(INVERSION_FOND);
				minitel.print(String(i + (MAX_SCORES / 2) + 1));
				minitel.attributs(FOND_NORMAL);
				minitel.print(" ");
				minitel.attributs(CARACTERE_CYAN);
				if (scoreToHighlight == (i + (MAX_SCORES / 2)))
					minitel.attributs(CLIGNOTEMENT);
				minitel.print(gamertag[i + (MAX_SCORES / 2)]);
				minitel.moveCursorXY(20 + 1 + 1 + 1 + 13 + 1, 7 + i * 2);
				minitel.attributs(CARACTERE_MAGENTA);
				if (scoreToHighlight == (i + (MAX_SCORES / 2)))
					minitel.attributs(CLIGNOTEMENT);
				writeTextRight(String(scores[i + (MAX_SCORES / 2)]), 3);
				if (scoreToHighlight == (i + (MAX_SCORES / 2)))
					minitel.attributs(FIXE);
			}
			scoreToHighlight = -1;
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
			writeCenter(theInput, 3, CARACTERE_BLANC, false);
			posX = 16;
			posY = 24;
			minitel.moveCursorXY(posX, posY);
			break;
		case PageQuestion:
			sendBytes(PAGE_QUESTION_SIZE, page_question);
			posX = 15;
			posY = 24;
			break;
		case PageAbandon:
			sendBytes(PAGE_HEADER_SIZE, page_header);
			minitel.moveCursorXY(3, 5);
			minitel.attributs(CARACTERE_BLEU);
			minitel.print("Trop tard !");
			writeTextInBox("Vous avez été trop long pour répondre, la partie est terminée.", 2, 8, 36, 4, CARACTERE_BLANC);
			writeCenter("Appuyez sur une touche", 12, CARACTERE_BLANC, true);
			break;
		case PageResultat:
			sendBytes(PAGE_RESULTAT_SIZE, page_resultat);
			writeCenter(theInput, 3, CARACTERE_CYAN, false);
			break;
		case PageSaisieNom:
			sendBytes(PAGE_HEADER_SIZE, page_header);
			minitel.moveCursorXY(3, 5);
			minitel.attributs(CARACTERE_BLEU);
			minitel.print("Entrez votre pseudo");
			writeTextInBox("Pour effectuez le classement et peut-être gagner un lot, nous avons besoin d'un pseudonyme afin de vous identifier.", 2, 8, 36, 4, CARACTERE_BLANC);
			minitel.moveCursorXY(2, 13);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print("Votre pseudo : .............");

			writeTextInBox("Pour corrigez, appuyez sur la touche 'CORRECTION'. Une fois terminé votre saisie, appuyez sur la touche verte 'ENVOI'.", 2, 15, 36, 4, CARACTERE_VERT);

			// chrono (bleu)
			minitel.moveCursorXY(23, 24);
			minitel.attributs(CARACTERE_BLEU);
			minitel.print("temps restant : 30");
			memoChrono = 30;
			posX = 17;
			posY = 13;
			minitel.moveCursorXY(posX, posY);
			minitel.cursor();
			startInput(13);
			break;
	}
	//minitelTimeLastCommand = 0;
}

void TheDisplay::writeCenter(String text, uint8_t y, byte color, bool blink)
{
	uint8_t x = (40 - text.length()) / 2;
	minitel.moveCursorXY(x, y);
	minitel.attributs(color);
	if(blink)
		minitel.attributs(CLIGNOTEMENT);
	minitel.print(text);
}

void TheDisplay::writeTextRight(String text, uint8_t width)
{
	for (uint8_t i = text.length(); i < width; i++)
		minitel.print(" ");
	minitel.print(text);
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
		minitel.attributs(color);
		minitel.print(temp.trim());
		currentPosText += lengthToGet;
		text = text.substring(currentPosText).trim();
		lengthToPut = text.length();
	}
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
	posX = 17;
	posY = 24;
	// wait
	minitel.moveCursorXY(posX, posY);
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
	if (
		(lastKey == CONNEXION_FIN) ||
		(lastKey == SOMMAIRE) ||
		(lastKey == ANNULATION) ||
		(lastKey == RETOUR) ||
		(lastKey == REPETITION) ||
		(lastKey == GUIDE) ||
		(lastKey == SUITE) ||
		(lastKey == ENVOI))
	{
		return true;
	}
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

void TheDisplay::showResult(uint8_t goodAnswers, uint8_t badAnswers, PlayerStatus status, String motto, uint16_t points)
{
	//minitel.attributs(FOND_JAUNE);
	minitel.moveCursorXY(17, 5);
	minitel.attributs(CARACTERE_BLEU);
	if (goodAnswers == 0)
		minitel.print("aucune bonne réponse !");
	if (goodAnswers == 1)
		minitel.print("1 bonne réponse / " + String(MAX_QUESTIONS_PER_GAME));
	if ((goodAnswers > 1) && (goodAnswers < MAX_QUESTIONS_PER_GAME))
		minitel.print(String(goodAnswers) + " bonnes réponses / " + String(MAX_QUESTIONS_PER_GAME));
	if (goodAnswers == MAX_QUESTIONS_PER_GAME)
		minitel.print("tout bon !");

	if (badAnswers == 0) {
		minitel.moveCursorXY(27, 7);
		minitel.attributs(CARACTERE_BLEU);
		minitel.print("aucune erreur !");
	}
	if (badAnswers == 1) {
		minitel.moveCursorXY(27, 7);
		minitel.attributs(CARACTERE_BLEU);
		minitel.print("soit " + String(badAnswers) + " erreur");
	}
	if ((badAnswers > 1) && (badAnswers < 10)) {
		minitel.moveCursorXY(26, 7);
		minitel.attributs(CARACTERE_BLEU);
		minitel.print("soit " + String(badAnswers) + " erreurs");
	}
	if ((badAnswers > 9) && (badAnswers < MAX_QUESTIONS_PER_GAME))
	{
		minitel.moveCursorXY(25, 7);
		minitel.attributs(CARACTERE_BLEU);
		minitel.print("soit " + String(badAnswers) + " erreurs");
	}
	if (badAnswers == MAX_QUESTIONS_PER_GAME)
	{
		minitel.moveCursorXY(31, 7);
		minitel.attributs(CARACTERE_BLEU);
		minitel.print("tout faux");
	}

	writeTextInBox(motto, 0, 12, 19, 3, CARACTERE_BLANC);

	switch(status) {
		case Human:
			minitel.moveCursorXY(0, 7);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print("Humain");
			sendBytes(RANG_HUMAN_SIZE, rang_human);
			//writeCenter("|__| |  |  |\\/|  /\\  | |\\ |", 8, CARACTERE_BLANC, false);
			//writeCenter("|  | \\__/  |  | /~~\\ | | \\|", 9, CARACTERE_BLANC, false);
			//writeCenter("", 10, CARACTERE_BLANC, false);
			break;
		case Sensitif:
			minitel.moveCursorXY(0, 7);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print("Sensitif");
			sendBytes(RANG_SENSITIF_SIZE, rang_sensitif);
			//writeCenter(" __   ___       __    ___    ___", 8, CARACTERE_BLANC, false);
			//writeCenter("/__  |__  |\\ | /__  |  |  | |__ ", 9, CARACTERE_BLANC, false);
			//writeCenter(".__/ |___ | \\| .__/ |  |  | |   ", 10, CARACTERE_BLANC, false);
			break;
		case Initie:
			minitel.moveCursorXY(0, 7);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print("Initié");
			sendBytes(RANG_INITIE_SIZE, rang_initie);
			//writeCenter("         ___    ___", 8, CARACTERE_BLANC, false);
			//writeCenter("| |\\ | |  |  | |__ ", 9, CARACTERE_BLANC, false);
			//writeCenter("| | \\| |  |  | |___", 10, CARACTERE_BLANC, false);
			break;
		case Padawan:
			minitel.moveCursorXY(0, 7);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print("Padawan");
			sendBytes(RANG_PADAWAN_SIZE, rang_padawan);
			//writeCenter(" __        __                     ", 8, CARACTERE_BLANC, false);
			//writeCenter("|__)  /\\  |  \\  /\\  |  |  /\\  |\\ |", 9, CARACTERE_BLANC, false);
			//writeCenter("|    /~~\\ |__/ /~~\\ |/\\| /~~\\ | \\|", 10, CARACTERE_BLANC, false);
			break;
		case Chevalier:
			minitel.moveCursorXY(0, 7);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print("Chevalier Jedi");
			sendBytes(RANG_CHEVALIER_SIZE, rang_chevalier);
			//writeCenter(" __        ___                  ___  __  ", 8, CARACTERE_BLANC, false);
			//writeCenter("/    |__| |__  \\  / /\\  |    | |__  |__) ", 9, CARACTERE_BLANC, false);
			//writeCenter("\\__, |  | |___  \\/ /~~\\ |___ | |___ |  \\ ", 10, CARACTERE_BLANC, false);
			break;
		case GrandMaitre:
			minitel.moveCursorXY(0, 7);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print("Grand Maître Jedi");
			sendBytes(RANG_MAITRE_SIZE, rang_maitre);
			//writeCenter("            ___  __   ___", 8, CARACTERE_BLANC, false);
			//writeCenter("|\\/|  /\\  |  |  |__) |__ ", 9, CARACTERE_BLANC, false);
			//writeCenter("|  | /~~\\ |  |  |  \\ |___", 10, CARACTERE_BLANC, false);
			break;
		}

		uint8_t x = 30;
		if(points < 100)
			x++;
		if(points < 10)
			x++;
		minitel.moveCursorXY(x, 15);
		minitel.attributs(CARACTERE_VERT);
		minitel.attributs(CLIGNOTEMENT);
		minitel.print(String(points));
		minitel.attributs(FIXE);
		minitel.print(" points");

		for (uint8_t i = 0; i < MAX_SCORES;i++)
		{
			if(scores[i] < points)
			{
				// on bat un score !
				// on décale le restant du tableau
				for (uint8_t j = MAX_SCORES - 2; j > i; j--)
				{
					scores[j] = scores[j - 1];
					gamertag[j] = gamertag[j - 1];
				}
				// on insère notre joueur
				scores[i] = points;
				gamertag[i] = theInput;
				scoreToHighlight = i;
				break;
			}
		}
}
