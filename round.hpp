/////////////////////////////////////////////
// round.hpp // letzte Änderung: 25.11.2017//
// letzte Editirung: Miguel				   //	
// Version: 0.1							   //	
// -------- Kommentare --------------------//
/*Miguel: benötige zugriff auf beide player via setPlayer oder so
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
	void changePlayer();
	bool checkWinCondition();
	double getCurrentRoundNumber() const;
	void setCurrentRoundNumber(const double);
	int getMaxRoundNumber() const;
};

class Phase
{
public:
	virtual void changePhase(Round*) = 0;
	virtual void changePlayer(Round*) = 0;
};

class MovePhase : public Phase
{
public:
    void changePhase(Round*);
    void changePlayer(Round*);
};

class AttackPhase : public Phase
{
public:
    void changePlayer(Round*);
    void changePhase(Round*);
};

#endif
