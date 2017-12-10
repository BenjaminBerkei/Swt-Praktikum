/////////////////////////////////////////////
// player.hpp // letzte Änderung: 10.12.17 //
// Letzte Editirung: Miguel				   //	
// Version: 0.2							   //	
// -------- Kommentare --------------------//
/* Arne: Ich bin mir unsicher bei dem Zeiger von Player*
   Miguel: erweitert um playerNo zur indifikation des Players

*/
/////////////////////////////////////////////

#ifndef UNIT_HPP
#define UNIT_HPP

#include <string> //String ist kein standard
#include <iostream> //zum testens

class Player 
{ 
private: 
    std::string str_playerName; //std:: heisst, dass du auf den standard namespace zugreifst, da liegen die meisten relevanten dinge, so auch string
    int int_playerScore;
    int int_playerTotalEnergie;
    int int_playerUnitNumber;
	static int int_playerNo; // muss 1 oder 2 sein

public: 
    Player( std::string, int = 0, int = 0, int = 0);
    ~Player();
    void print() const; // nur zum testen
    std::string getPlayerName() const;	//const correctness, heßt das diese Funktion keinen wert verändern wird, damit umgeht man iA Fehler die aus versehen passieren
    int getPlayerScore() const;
    int getPlayerTotalEnergie() const;
    int getPlayerUnitNumber() const;
	int getPlayerNo() const;
    
    void setPlayerName(std::string);
    void setPlayerScore(int);
    void setPlayerTotalEnergie(int);
    void setPlayerUnitNumber(int);
	
	Player changePlayer(Player&);
};

#endif