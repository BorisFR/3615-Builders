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
	if(countSuccessiveGood > 4 && currentLevel < NUMBER_QCM_LEVEL)
	{
		currentLevel++;
	}
	// au contraire, si le joueur enchaîne les mauvaises réponses
	// alors on baisse le niveau
	if(countSuccessiveBad > 1 && currentLevel > 1)
	{
		currentLevel--;
	}

	// on choisit une question au hazard
	uint16_t index = random(numberQuestionsByLevel[currentLevel]);
	// si la question a déjà été posée
	while(isAlreadyAsk(index))
	{
		// on en choisit une autre
		index = random(numberQuestionsByLevel[currentLevel]);
	}
	// la question est choisie
	indexReal = index;
	// on mémorise le fait que l'on ait posé cette question au joueur
	questionsInGame[currentQuestion] = indexReal;

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
	// TODO:
	badAnswers++;
}

bool Game::isAnswerGood()
{
	// TODO: 
	return false;
}

uint8_t Game::getCurrentQuestionNumber()
{
	return currentQuestion + 1;
}

String Game::getCurrentQuestion()
{
	return qcmQuestions[indexReal];
}

String Game::getCurrentCategory()
{
	switch(qcmCategories[indexReal])
	{
		case 0: return "Cinéma";
		case 1: return "Connaissance";
		case 2: return "Droïde";
		case 3: return "Histoire";
	}
	return String(qcmCategories[indexReal]);
}

String Game::getCurrentAnswer1()
{
	return qcmAnswers[indexReal];
}

String Game::getCurrentAnswer2()
{
	return qcmFalse1[indexReal];
}

String Game::getCurrentAnswer3()
{
	return qcmFalse2[indexReal];
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
	// TODO; 
	return Padawan;
}

String Game::getPlayerMoto()
{
	// TODO; 
	return "Moto";
}
