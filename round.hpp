/////////////////////////////////////////////
// round.hpp // letzte Änderung: 25.11.2017//
// letzte Editirung: Miguel				   //	
// Version: 0.2						   //	
// -------- Kommentare --------------------//
/*es gibt wie über whatsapp besprochen nur noch changePhase()
*/
/////////////////////////////////////////////

#ifndef ROUND_HPP
#define ROUND_HPP

class Phase;

class Round
{
private:
	int int_maxRoundNumber;
	double double_currentRoundNumber;
	Phase* currentRoundPhase;

public:
	Round(int);
	~Round();
	void setCurrentRoundPhase(Phase*);
	void changePhase();
	bool checkWinCondition();
	double getCurrentRoundNumber() const;
	void setCurrentRoundNumber(const double);
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

class AttackPhase : public Phase
{
public:
    void changePlayer(Round*);
};

#endif
