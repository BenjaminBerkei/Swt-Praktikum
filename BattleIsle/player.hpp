/////////////////////////////////////////////
// player.hpp // letzte Änderung: 03.01.18 //
// Letzte Editirung: Miguel				   //	
// Version: 0.3							   //	
// -------- Kommentare --------------------//
/* Arne: Ich bin mir unsicher bei dem Zeiger von Player*
   Miguel: erweitert um playerNo zur indifikation des Players
			->geändert wie abgesprochen!
*/
/////////////////////////////////////////////

#ifndef UNIT_HPP
#define UNIT_HPP

#include "game.hpp"
#include <QString> 

class Player 
{ 
private: 
    Qstring str_playerName; 
    int int_playerScore;
    int int_playerTotalEnergie;
	int int_currentEnergieStorage;
    int int_playerUnitNumber;

public: 
    Player( QString, int = 0, int = 0, int = 0, int = 0);
    ~Player();

	QString getPlayerName() const;	//const correctness, heßt das diese Funktion keinen wert verändern wird, damit umgeht man iA Fehler die aus versehen passieren
    int getPlayerScore() const;
    int getPlayerTotalEnergie() const;
	int getCurrentEnergieStorage const;
    int getPlayerUnitNumber() const;
    
    void setPlayerName(QString);
    void setPlayerScore(int);
    void setPlayerTotalEnergie(int);
	void setCurrentEnergieStorage(int);
    void setPlayerUnitNumber(int);
	
};

#endif