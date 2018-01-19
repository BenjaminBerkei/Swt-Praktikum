/* Author: Miguel
 * Version: 0.3
 * Datum 03.01.2018
 * Kommentare: Arne: Ich bin mir unsicher bei dem Zeiger von Player*
->geändert wie abgesprochen!
 * */
/* Author: Lucas
 * Version: 0.4
 * Datum 14.01.20118
 * Kommentare: bool für HQ destroyed eingefügt, increase-/decreaseUnitNumber() Hilfsfunktionen geschrieben
 * */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QString> 

class Game;

class Player 
{ 
private: 
    QString str_playerName;
    const int int_playerID;
    int int_playerScore;
    int int_playerTotalEnergie;
	int int_currentEnergieStorage;
    int int_playerUnitNumber;
    bool bool_HQDestroyed;

public: 
    Player(QString, int, int = 1000, int = 1000, int = 0, int = 0);
    ~Player();
    void increaseUnitNumber();
    void decreaseUnitNumber();

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
	
    int getPlayerID() const;
    bool getHQDestroyed() const;
    void setHQDestroyed(bool value);
};

#endif
