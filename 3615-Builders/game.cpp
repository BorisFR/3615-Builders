#include "Game.hpp"

void Game::setup()
{
	randomSeed(now());
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
		questionByLevel[ qcmLevel[i] - 1 ][ numberQuestionsByLevel[qcmLevel[i] - 1] ] = i;
		// on compte le nombre de questions par niveaux
		numberQuestionsByLevel[ qcmLevel[i] - 1 ]++;
	}
}

bool Game::isAlreadyAsk(uint16_t indexQuestion)
{
	for(uint8_t i = 0; i < currentQuestion; i++)
	{
		if(questionsInGame[i] == indexQuestion)
		{
#ifdef DEBUG
			Serial.print(" .. ");
#endif
			return true;
		}
	}
#ifdef DEBUG
	Serial.print(" . ");
#endif
	return false;
}

void Game::prepareOneQuestion()
{
	Serial.println("Question : " + String(currentQuestion) + " - Tirage aléatoire");
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
#ifdef DEBUG
	Serial.println("Level: " + String(currentLevel) + " => Number of questions: " + String(numberQuestionsByLevel[currentLevel - 1]));
#endif
	// on choisit une question au hazard
	uint16_t index = random(numberQuestionsByLevel[currentLevel - 1]);
#ifdef DEBUG
	Serial.print("Trying " + String(index));
#endif
	indexReal = questionByLevel[currentLevel - 1][index];
#ifdef DEBUG
	Serial.print("[" + String(indexReal) + "] ");
	Serial.send_now();
#endif
	// si la question a déjà été posée
	while (isAlreadyAsk(indexReal))
	{
		// on en choisit une autre
		index = random(numberQuestionsByLevel[currentLevel - 1]);
#ifdef DEBUG
		Serial.print("=> " + String(index));
#endif
		indexReal = questionByLevel[currentLevel - 1][index];
#ifdef DEBUG
		Serial.print("[" + String(indexReal) + "] ");
		Serial.send_now();
#endif
	}
#ifdef DEBUG
	Serial.println("OK");
#endif
	// la question est choisie
	// on mémorise le fait que l'on ait posé cette question au joueur
	questionsInGame[currentQuestion] = indexReal;
	questionsID[currentQuestion] = qcmUUID[indexReal];
	switch(random(3))
	{
		case 0:
#ifdef DEBUG
			Serial.println("Shuffle answer case 0");
#endif
			currentGoodAnswer = 1;
			answer1 = qcmAnswers[indexReal];
			answer2 = qcmFalse1[indexReal];
			answer3 = qcmFalse2[indexReal];
			break;
		case 1:
#ifdef DEBUG
			Serial.println("Shuffle answer case 1");
#endif
			currentGoodAnswer = 2;
			answer2 = qcmAnswers[indexReal];
			answer1 = qcmFalse1[indexReal];
			answer3 = qcmFalse2[indexReal];
			break;
		case 2:
#ifdef DEBUG
			Serial.println("Shuffle answer case 2");
#endif
			currentGoodAnswer = 3;
			answer3 = qcmAnswers[indexReal];
			answer1 = qcmFalse1[indexReal];
			answer2 = qcmFalse2[indexReal];
			break;
	}

	timeToAnswer = 0;

#ifdef DEBUG
	Serial.send_now();
#endif
	// TODO: bosser avec qcmUUID
	// compter cmbien de fois la question est sortie
	// et le nombre de bonnes et fausses réponses
}

void Game::startNewGame(uint8_t level, uint16_t numberQuestions)
{
#ifdef DEBUG
	Serial.println("Starting new game");
#endif
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
	points = 0;
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
		Serial.println("Game end");
		Serial.send_now();
		return true;
	}
	return false;
}

void Game::playAnswer(uint8_t answer)
{
	unsigned long delay = timeToAnswer;

	if (answer == currentGoodAnswer)
	{
		answerinGame[currentQuestion] = 1;
		goodAnswers++;
		giveGoodAnswer = true;
		countSuccessiveGood++;
		countSuccessiveBad = 0;
		unsigned long ptsDelay = 6 - ((delay / 1000) / 5);
#ifdef DEBUG
		Serial.print("** Current score:" + String(points) + " => delay:" + String(delay) + "=" + String(ptsDelay));
#endif
		points += (2 * currentLevel) + ptsDelay;
#ifdef DEBUG
		Serial.println(" ** New score:" + String(points));
#endif
	}
	else
	{
		answerinGame[currentQuestion] = 1;
		badAnswers++;
		giveGoodAnswer = false;
		countSuccessiveBad++;
		countSuccessiveGood = 0;
	}
#ifdef DEBUG
	Serial.send_now();
#endif
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
	if (goodAnswers < (MAX_QUESTIONS_PER_GAME / 3))
		return Sensitif;
	if (goodAnswers < (MAX_QUESTIONS_PER_GAME / 2))
		return Initie;
	if (goodAnswers < (2 * MAX_QUESTIONS_PER_GAME / 3))
		return Padawan;
	if (goodAnswers < (MAX_QUESTIONS_PER_GAME - 1))
		return Chevalier;
	return GrandMaitre;
}

String Game::getPlayerMotto()
{
	if (goodAnswers == 0)
		return HUMAN_MOTTO;
	if (goodAnswers < (MAX_QUESTIONS_PER_GAME / 3))
		return SENSITIF_MOTTO;
	if (goodAnswers < (MAX_QUESTIONS_PER_GAME / 2))
		return INITIE_MOTTO;
	if (goodAnswers < (2 * MAX_QUESTIONS_PER_GAME / 3))
		return PADAWAN_MOTTO;
	if (goodAnswers < (MAX_QUESTIONS_PER_GAME - 1))
		return CHEVALIER_MOTTO;
	return MASTER_MOTTO;
}

uint16_t Game::getPoints()
{
	return points;
}