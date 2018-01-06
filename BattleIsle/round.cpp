//////////////////////////////////////////////////
// round.cpp // letzte Änderung: 20.12.2017	//
// letzte Editirung: Miguel			//	
// Version: 0.3					//	
// -------- Kommentare -------------------------//
/*sieh round.hpp
*/
/////////////////////////////////////////////

#include "round.hpp"

Round::Round(int maxAnz = 0)
{
    int_maxRoundNumber=maxAnz*10;
    int_currentRoundNumber=10;
	currentRoundPhase = new MovePhase;
	return;
}

Round::~Round()
{
	delete currentRoundPhase;
	return;
}

void Round::setCurrentRoundPhase(Phase* phase)
{
	delete currentRoundPhase;
	currentRoundPhase = phase;
	return;
}

void Round::changePhase()
{
	currentRoundPhase->changePhase(this);
	return;
}

bool Round::checkWinCondition()
{
	if(int_currentRoundNumber >= int_maxRoundNumber && int_maxRoundNumber != 0)
	{
		return true;
	}
	else
	{
	return false;
	}
}

int Round::getCurrentRoundNumber() const
{
	return int_currentRoundNumber;
}

int Round::getMaxRoundNumber() const
{
	return int_maxRoundNumber;
}

void Round::setCurrentRoundNumber(const int roundAnz)
{
	int_currentRoundNumber = roundAnz;
	return;
}

void MovePhase::changePhase(Round* round)
{
	round->setCurrentRoundPhase(new ActionPhase);
	return;
}

void ActionPhase::changePhase(Round* round)
{
	round->setCurrentRoundPhase(new MovePhase);
	round->setCurrentRoundNumber(round->getCurrentRoundNumber() + 5);
}
