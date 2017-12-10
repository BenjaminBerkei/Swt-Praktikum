/////////////////////////////////////////////
// player.cpp // letzte Änderung: 28.11.2017 //
// Letzte Editirung: Arne				   //	
// Version: 0.1							   //	
// -------- Kommentare --------------------//
/* Arne: Ich bin mir unsicher bei dem Zeiger von Player*

*/
/////////////////////////////////////////////

#include "player.hpp"

Player::Player(	std::string playerName,
    		int playerScore,
    		int playerTotalEnergie,
    		int playerUnitNumber )
{
	str_playerName = playerName;
    int_playerScore = playerScore;
    int_playerTotalEnergie = playerTotalEnergie;
    int_playerUnitNumber = playerUnitNumber;
	return;
}

Player::~Player(){
	/*
	 * Delete nur wenn du mit new speicher allociert hast
	 */
	return;
}
/*Ausgabe zu testzwecken*/
void Player::print() const
{
	std::cout << "Spieler " << str_playerName <<  std::endl
		<< "Score " << int_playerScore << std::endl
		<< "Energie " << int_playerTotalEnergie << std::endl
		<< "Unit Number " << int_playerUnitNumber << std::endl;
}
void Player::setPlayerName(std::string str_name){ //Du musst dieselbe Signatur wie in der hpp datei verwenden
	str_playerName = str_name;
	//Äquivalent wäre (*this).str_playerName = str_name;
	return;
}

void Player::setPlayerScore(int int_score){	//s.o
	int_playerScore = int_score;
	return;
}

void Player::setPlayerTotalEnergie(int int_energie){	//s.o
	int_playerTotalEnergie = int_energie;
	return;
}

void Player::setPlayerUnitNumber(int int_number){	//s.o
	int_playerUnitNumber = int_number;
	return;
}

std::string Player::getPlayerName() const	//siehe .hpp kommentar zu strings & const correctness
{
	return str_playerName;
}

int Player::getPlayerScore() const
{
	return int_playerScore;
}

int Player::getPlayerTotalEnergie() const
{
	return int_playerScore;
}

int Player::getPlayerUnitNumber() const
{
	return int_playerUnitNumber;
}