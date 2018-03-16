#include "TheDisplay.hpp"

Minitel minitel(SERIAL_MINITEL);


void TheDisplay::generateQrCode(String value)
{
    uint8_t qrcodeData[qrcode_getBufferSize(QR_CODE_VERSION)];
	Serial.println("[QRcode] generating");
	qrcode_initText(&qrcode, qrcodeData, QR_CODE_VERSION, 0, value.c_str());
	for (uint8_t y = 0; y < qrcode.size; y++)
	{
		lines[y] = "";
		for (uint8_t x = 0; x < qrcode.size; x++) {
			//Serial.print(qrcode_getModule(&qrcode, x, y) ? "\u2588": " ");
			lines[y] += qrcode_getModule(&qrcode, x, y) ? "1" : "0";
		}
		//Serial.println(lines[y]);
	}
}

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
	theInput = "*** Boris ***";
	clearHiScores();
}

void TheDisplay::clearHiScores()
{
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
	gamertag[9] =  "*  à toi de  *";
	gamertag[10] = "*    jouer   *";
	gamertag[11] = "";
	gamertag[12] = " --  Amiens -- ";
	gamertag[13] = "";
	gamertag[14] = "";
	gamertag[15] = "";
	gamertag[16] = "";
	gamertag[17] = "";
	scoreToHighlight = -1;
}

void TheDisplay::bip()
{
	minitel.bip();
}


String TheDisplay::on2(uint8_t value)
{
	if(value < 10)
		return "0" + String(value);
	return String(value);
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

char TheDisplay::getTextKey()
{
	if (lastKey >= 32 && lastKey <= 126)
	{
		char x = ' ' + (lastKey - 32);
		return x;
	}
	if(lastKey == ENVOI)
	{
		return 0x0d;
	}
	return ' ';
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

void TheDisplay::setQRcodeDisplay(bool value)
{
	showQRcode = value;
}

void TheDisplay::showPage(MINITEL_PAGE page)
{
	String fullDate;
	isInInputTextMode = false;
	// TODO: intégrer les pages manquantes
	switch(page)
	{
		case PageConfiguration:
			sendBytes(PAGE_HEADER_SIZE, page_header);
			minitel.moveCursorXY(3, 5);
			minitel.attributs(CARACTERE_BLEU);
			minitel.print("Configuration");

			minitel.moveCursorXY(1, 8);
			minitel.attributs(CARACTERE_VERT);
			minitel.attributs(INVERSION_FOND);
			minitel.print("C");
			minitel.attributs(FOND_NORMAL);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print(" Mettre les hi-scores à zéro");

			minitel.moveCursorXY(1, 9);
			minitel.attributs(CARACTERE_VERT);
			minitel.attributs(INVERSION_FOND);
			minitel.print("L");
			minitel.attributs(FOND_NORMAL);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print(" Charger les hi-scores du jour");

			minitel.moveCursorXY(1, 10);
			minitel.attributs(CARACTERE_VERT);
			minitel.attributs(INVERSION_FOND);
			minitel.print("A");
			minitel.attributs(FOND_NORMAL);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print(" Charger les hi-scores du matin");

			minitel.moveCursorXY(1, 11);
			minitel.attributs(CARACTERE_VERT);
			minitel.attributs(INVERSION_FOND);
			minitel.print("P");
			minitel.attributs(FOND_NORMAL);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print(" Charger les hi-scores de l'après midi");

			minitel.moveCursorXY(1, 12);
			minitel.attributs(CARACTERE_VERT);
			minitel.attributs(INVERSION_FOND);
			minitel.print("H");
			minitel.attributs(FOND_NORMAL);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print(" Matin /après midi à ");
			minitel.print(String(midi));
			minitel.print(":00");

			minitel.moveCursorXY(1, 13);
			minitel.attributs(CARACTERE_VERT);
			minitel.attributs(INVERSION_FOND);
			minitel.print("Q");
			minitel.attributs(FOND_NORMAL);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print(" Affiche le QRcode : ");
			if(showQRcode)
				minitel.print("oui");
			else
				minitel.print("non");

			minitel.moveCursorXY(1, 14);
			minitel.attributs(CARACTERE_VERT);
			minitel.attributs(INVERSION_FOND);
			minitel.print("J");
			minitel.attributs(FOND_NORMAL);
			minitel.attributs(CARACTERE_BLANC);
			minitel.print(" QRcode classement joueurs : " + String(playerOnPodium));
			minitel.moveCursorXY(3, 15);
			minitel.attributs(CARACTERE_VERT);
			minitel.print("(QRcode non affiché pour les autres)");

			//writeTextInBox("Vous avez été trop long pour répondre, la partie est terminée.", 2, 8, 36, 4, CARACTERE_BLANC);
			writeCenter("Appuyez sur ENVOI pour quitter", 24, CARACTERE_BLANC, true);
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
			fullDate = String(hour()) + ":";
			if(minute() < 10)
				fullDate += "0";
			fullDate += String(minute()) + " " + weekDays[weekday() - 1] + " " + String(day()) + " " + monthsName[month() - 1] + " " + String(year());
			writeCenter(fullDate, 24, CARACTERE_BLEU, false);
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

		case PageQRcode:
			sendBytes(90, page_header); // on enleve le cadre
			//sendBytes(PAGE_HEADER_SIZE, page_header);
			//minitel.moveCursorXY(3, 5);
			//minitel.attributs(CARACTERE_BLEU);
			//minitel.print("Votre QRcode");

			minitel.textMode();
			writeCenter("Prenez ce QRcode en photo !", 3, CARACTERE_BLANC, true);
			minitel.attributs(FIXE);

			String text = String(day()) + "/" + String(month()) + "/" + String(year()) +
						  " a " + String(on2(hour())) + ":" + String(on2(minute())) + ":" + String(on2(second())) +
						  " " + gamerName + " " + String(gamerPoints);

			writeCenter(text, 24, CARACTERE_ROUGE, false);

			generateQrCode(text.toUpperCase());

			Serial.println("[QRcode]" + String(qrcode.size) + "x" + String(qrcode.size) + " sending to Minitel");
			/* QRcode en taille 1:1
			uint8_t y = 0;
			while (y < qrcode.size)
			{
				minitel.moveCursorXY(3, 8 + (y / 3));
				minitel.graphicMode();
				minitel.attributs(CARACTERE_BLANC);
				
				for (uint8_t x = 0; x < qrcode.size; x += 2)
				{
					byte gfx = 0;
					if (lines[y].substring(x, x + 1) == "1")
						gfx += 32;
					if (lines[y].substring(x + 1, x + 2) == "1")
						gfx += 16;
					if (lines[y + 1].substring(x, x + 1) == "1")
						gfx += 8;
					if (lines[y + 1].substring(x + 1, x + 2) == "1")
						gfx += 4;
					if (lines[y + 2].substring(x, x + 1) == "1")
						gfx += 2;
					if (lines[y + 2].substring(x + 1, x + 2) == "1")
						gfx += 1;
					minitel.graphic(gfx);
				}
				y += 3;
			}*/
			// QRcode en double taille
			uint8_t y = 0;
			uint8_t posY = 4;
			while (y < qrcode.size)
			{
				uint8_t posX = 7;
				//Serial.print(String(y) + ":");
				for (uint8_t x = 0; x < qrcode.size; x += 2)
				{
					//Serial.print(String(x) + " ");
					minitel.moveCursorXY(posX + x, posY);
					if (x == 0) {
						minitel.graphicMode();
						minitel.attributs(CARACTERE_BLANC);
					}
					byte gfx1 = 0;
					byte gfx2 = 0;
					byte gfx3 = 0;
					byte gfx4 = 0;
					if (lines[y].substring(x, x + 1) == "1")
						gfx1 += 32 + 16 + 8 + 4;
					if (lines[y].substring(x + 1, x + 2) == "1")
						gfx2 += 32 + 16 + 8 + 4;
					if (lines[y + 1].substring(x, x + 1) == "1")
						gfx1 += 2 + 1;
					if (lines[y + 1].substring(x + 1, x + 2) == "1")
						gfx2 += 2 + 1;
					if (lines[y + 1].substring(x, x + 1) == "1")
						gfx3 += 32 + 16;
					if (lines[y + 1].substring(x + 1, x + 2) == "1")
						gfx4 += 32 + 16;
					if (lines[y + 2].substring(x, x + 1) == "1")
						gfx3 += 8 + 4 + 2 + 1;
					if (lines[y + 2].substring(x + 1, x + 2) == "1")
						gfx4 += 8 + 4 + 2 + 1;
					minitel.graphic(gfx1);
					minitel.graphic(gfx2);
					minitel.moveCursorXY(posX + x, posY + 1);
					if(x==0) {
						minitel.graphicMode();
					}
					minitel.attributs(CARACTERE_BLANC);

					minitel.graphic(gfx3);
					minitel.graphic(gfx4);
				}
				//Serial.println();
				posY += 2;
				y += 3;
			}
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
		(lastKey == SUITE))
	{
		return true;
	}
	return false;
}

void TheDisplay::clearKeyboard()
{
	keyIsPressed = false;
	lastKey = 0;
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

void TheDisplay::showResult(String gamer, uint8_t goodAnswers, uint8_t badAnswers, PlayerStatus status, String motto, uint16_t points)
{
	Serial.println("Showing result");
	minitel.moveCursorXY(17, 5);
	minitel.attributs(CARACTERE_BLEU);
	if (goodAnswers == 0)
		minitel.print("aucune bonne réponse !");
	else {
		if (goodAnswers == 1)
			minitel.print("1 bonne réponse / " + String(MAX_QUESTIONS_PER_GAME));
		else {
			if ((goodAnswers > 1) && (goodAnswers < MAX_QUESTIONS_PER_GAME))
				minitel.print(String(goodAnswers) + " bonnes réponses / " + String(MAX_QUESTIONS_PER_GAME));
			else {
				if (goodAnswers == MAX_QUESTIONS_PER_GAME)
					minitel.print("tout bon !");
			}
		}
	}

	if (badAnswers == 0) {
		minitel.moveCursorXY(27, 7);
		minitel.attributs(CARACTERE_BLEU);
		minitel.print("aucune erreur !");
	} else {
		if (badAnswers == 1) {
			minitel.moveCursorXY(27, 7);
			minitel.attributs(CARACTERE_BLEU);
			minitel.print("soit " + String(badAnswers) + " erreur");
		} else {
			if ((badAnswers > 1) && (badAnswers < 10)) {
				minitel.moveCursorXY(26, 7);
				minitel.attributs(CARACTERE_BLEU);
				minitel.print("soit " + String(badAnswers) + " erreurs");
			} else {
				if ((badAnswers > 9) && (badAnswers < MAX_QUESTIONS_PER_GAME))
				{
					minitel.moveCursorXY(25, 7);
					minitel.attributs(CARACTERE_BLEU);
					minitel.print("soit " + String(badAnswers) + " erreurs");
				} else {
					if (badAnswers == MAX_QUESTIONS_PER_GAME)
					{
						minitel.moveCursorXY(31, 7);
						minitel.attributs(CARACTERE_BLEU);
						minitel.print("tout faux");
					}
				}
			}
		}
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

		/*String text = String(day()) + "/" + String(month()) + "/" + String(year()) +
					  " a " + String(on2(hour())) + ":" + String(on2(minute())) + ":" + String(on2(second())) +
					  " - Joueur : " + gamer + " - Score : " + String(points);

		generateQrCode(text.toUpperCase());*/
		gamerName = gamer;
		gamerPoints = points;
}

bool TheDisplay::onPodium()
{
	if (scoreToHighlight <= playerOnPodium)
		return true;
	return false;
}

void TheDisplay::setHiScore(uint8_t place, String name, uint16_t points)
{
	scores[place] = points;
	gamertag[place] = name;
}

void TheDisplay::setPlayerPodium(uint8_t value)
{
	playerOnPodium = value;
}

void TheDisplay::setMidi(uint8_t value)
{
	midi = value;
}
