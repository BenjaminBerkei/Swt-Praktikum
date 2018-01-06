/////////////////////////////////////////////
// player.hpp // letzte Änderung: 03.01.18 //
// Letzte Editirung: Miguel				   //	
// Version: 0.3							   //	
// -------- Kommentare --------------------//
/* Arne: Ich bin mir unsicher bei dem Zeiger von Player*
			->geändert wie abgesprochen!
*/
/////////////////////////////////////////////

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game.h"
#include <QString> 

class Player 
{ 
private: 
    QString str_playerName;
    int int_playerScore;
    int int_playerTotalEnergie;
	int int_currentEnergieStorage;
    int int_playerUnitNumber;

public: 
    Player(QString, int, int, int, int);
    ~Player();

	QString getPlayerName() const;	//const correctness, heßt das diese Funktion keinen wert verändern wird, damit umgeht man iA Fehler die aus versehen passieren
    int getPlayerScore() const;
    int getPlayerTotalEnergie() const;
    int getCurrentEnergieStorage() const;
    int getPlayerUnitNumber() const;
    
    void setPlayerName(QString);
    void setPlayerScore(int);
    void setPlayerTotalEnergie(int);
	void setCurrentEnergieStorage(int);
    void setPlayerUnitNumber(int);
	
};

#endif
