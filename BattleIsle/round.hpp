/////////////////////////////////////////////
// round.hpp // letzte Änderung: 25.11.2017//
// letzte Editirung: Miguel				   //	
// Version: 0.3						   //	
// -------- Kommentare --------------------//
/*es gibt wie über whatsapp besprochen nur noch changePhase()
0.3 -> runde in 10er schritten
*/
/////////////////////////////////////////////

#ifndef ROUND_HPP
#define ROUND_HPP

class Phase;

class Round
{
private:
	int int_maxRoundNumber;
	int int_currentRoundNumber;
	Phase* currentRoundPhase;

public:
	Round(int);
	~Round();
	void setCurrentRoundPhase(Phase*);
	void changePhase();
	bool checkWinCondition();
	int getCurrentRoundNumber() const;
	void setCurrentRoundNumber(const int);
	int getMaxRoundNumber() const;
};

class Phase
{
public:
	virtual void changePhase(Round*) = 0;
};

class MovePhase : public Phase
{
public:
    void changePhase(Round*);
};

class ActionPhase : public Phase
{
public:
    void changePhase(Round*);
};

#endif
