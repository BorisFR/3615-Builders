#include "Game.hpp"

void Game::setup()
{
	randomSeed(analogRead(0));
	parseQCM();
}

void Game::loop()
{

}

void Game::parseQCM()
{
	for(uint8_t i = 0; i < NUMBER_QCM_LEVEL; i++)
	{
		numberQuestionsByLevel[i] = 0;
	}

	for(uint16_t i = 0; i < NUMBER_QCM_QUESTIONS; i++)
	{
		// question n° i
		// niveau = qcmLevel[i] (de 1 à 5)
		// n° de question pour le niveau = numberQuestionsByLevel[ qcmLevel[i] ]
		// on mémorise la question pour chacun des niveaux
		questionByLevel[ qcmLevel[i] ][ numberQuestionsByLevel[qcmLevel[i]] ] = i;
		// on compte le nombre de questions par niveaux
		numberQuestionsByLevel[ qcmLevel[i] ]++;
	}
}

bool Game::isAlreadyAsk(uint16_t indexQuestion)
{
	for(uint8_t i = 0; i < currentQuestion; i++)
	{
		if(questionsInGame[i] == indexQuestion)
		{
			return true;
		}
	}
	return false;
}

void Game::prepareOneQuestion()
{
	// si le joueur enchaîne les bonnes réponses
	// on passe au niveau supérieur
	if (countSuccessiveGood >= GOOD_ANSWER_TO_LEVEL_UP && currentLevel < NUMBER_QCM_LEVEL)
	{
		currentLevel++;
		countSuccessiveGood = 0;
		#ifdef DEBUG
			Serial.println("** Next level");
		#endif
	}
	// au contraire, si le joueur enchaîne les mauvaises réponses
	// alors on baisse le niveau
	if (countSuccessiveBad >= BAD_ANSWER_TO_LEVEL_DOWN && currentLevel > 1)
	{
		currentLevel--;
#ifdef DEBUG
		Serial.println("** Previous level");
#endif
	}

	// on choisit une question au hazard
	uint16_t index = random(numberQuestionsByLevel[currentLevel]);
	indexReal = questionByLevel[currentLevel][index];
	// si la question a déjà été posée
	while (isAlreadyAsk(indexReal))
	{
		// on en choisit une autre
		index = random(numberQuestionsByLevel[currentLevel]);
		indexReal = questionByLevel[currentLevel][index];
	}
	// la question est choisie
	// on mémorise le fait que l'on ait posé cette question au joueur
	questionsInGame[currentQuestion] = indexReal;
	switch(random(3))
	{
		case 0:
			currentGoodAnswer = 1;
			answer1 = qcmAnswers[indexReal];
			answer2 = qcmFalse1[indexReal];
			answer3 = qcmFalse2[indexReal];
			break;
		case 1:
			currentGoodAnswer = 2;
			answer2 = qcmAnswers[indexReal];
			answer1 = qcmFalse1[indexReal];
			answer3 = qcmFalse2[indexReal];
			break;
		case 2:
			currentGoodAnswer = 3;
			answer3 = qcmAnswers[indexReal];
			answer1 = qcmFalse1[indexReal];
			answer2 = qcmFalse2[indexReal];
			break;
		}

		// TODO: bosser avec qcmUUID
		// compter cmbien de fois la question est sortie
		// et le nombre de bonnes et fausses réponses
}

void Game::startNewGame(uint8_t level, uint16_t numberQuestions)
{
	startLevel = level;
	currentLevel = level;
	currentMaxQuestions = numberQuestions;
	for(uint8_t i = 0; i < MAX_QUESTIONS_PER_GAME; i++)
	{
		questionsInGame[i] = -1;
	}
	currentQuestion = 0;
	countSuccessiveGood = 0;
	countSuccessiveBad = 0;
	goodAnswers = 0;
	badAnswers = 0;
	prepareOneQuestion();
}

void Game::nextQuestion()
{
	if((currentQuestion + 1) == currentMaxQuestions)
	{
		return;
	}
	currentQuestion++;
	prepareOneQuestion();
}

bool Game::isGameFinish()
{
	if((currentQuestion + 1) == currentMaxQuestions)
	{
		return true;
	}
	return false;
}

void Game::playAnswer(uint8_t answer)
{
	if (answer == currentGoodAnswer)
	{
		goodAnswers++;
		giveGoodAnswer = true;
		countSuccessiveGood++;
		countSuccessiveBad = 0;
	} else {
		badAnswers++;
		giveGoodAnswer = false;
		countSuccessiveBad++;
		countSuccessiveGood = 0;
	}
}

bool Game::isAnswerGood()
{
	return giveGoodAnswer;
}

uint8_t Game::getCurrentQuestionNumber()
{
	return currentQuestion + 1;
}

uint8_t Game::getCurrentQuestionLevel()
{
	return currentLevel;
}

String Game::getCurrentQuestion()
{
	return qcmQuestions[indexReal];
}

String Game::getCurrentCategory()
{
	switch(qcmCategories[indexReal])
	{
		case 0: return CATEGORY_CINEMA;
		case 1: return CATEGORY_KNOWLEDGE;
		case 2: return CATEGORY_DROIDE;
		case 3: return CATEGORY_HISTORY;
	}
	return String(qcmCategories[indexReal]);
}

String Game::getCurrentAnswer1()
{
	return answer1;
}

String Game::getCurrentAnswer2()
{
	return answer2;
}

String Game::getCurrentAnswer3()
{
	return answer3;
}

uint8_t Game::getNumberOfGoodAnswers()
{
	return goodAnswers;
}

uint8_t Game::getNumberOfBadAnswers()
{
	return badAnswers;
}

PlayerStatus Game::getPlayerStatus()
{
	if (goodAnswers == 0)
		return Human;
	if (goodAnswers < 6)
		return Sensitif;
	if (goodAnswers < 11)
		return Initie;
	if (goodAnswers < 15)
		return Padawan;
	if (goodAnswers < 19)
		return Chevalier;
	return GrandMaitre;
}

String Game::getPlayerMotto()
{
	if (goodAnswers == 0)
		return "Star Wars, ça vous cause ?";
	if (goodAnswers < 6)
		return "Vous êtes sensible à la Force, continuez votre découverte.";
	if (goodAnswers < 11)
		return "La Force est en vous, découvrez vos possibilités.";
	if (goodAnswers < 15)
		return "La Force vous guide, approfondissez vos connaissances.";
	if (goodAnswers < 19)
		return "Votre sagesse vous honore, partagez votre savoir.";
	return "Votre maîtrise de la Force est exemplaire !";
}
