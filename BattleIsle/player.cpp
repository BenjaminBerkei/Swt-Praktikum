/////////////////////////////////////////////
// player.cpp // letzte Änderung: 03.01.18 //
// Letzte Editirung: Miguel				   //	
// Version: 0.3							   //	
// -------- Kommentare --------------------//
/* sie hpp datei

*/
/////////////////////////////////////////////

#include "player.hpp"

Player::Player(	Qtring playerName, int playerScore, int totalEnergie, int currentEnergie, int unitNumber )
	:str_playerName(playerName), int_playerScore(playerScore), int_playerTotalEnergie(totalEnergie), int_currentEnergieStorage(currentEnergie), int_playerUnitNumber(unitNumber) {}

Player::~Player(){
	/*
	 * Delete nur wenn du mit new speicher allociert hast
	 */
	return;
}

void Player::setPlayerName(QString name){ 
	str_playerName = name;
	return;
}

void Player::setPlayerScore(int score){
	int_playerScore = score;
	return;
}

void Player::setPlayerTotalEnergie(int energie){	
	int_playerTotalEnergie = energie;
	return;
}

void Player::setPlayerUnitNumber(int number){	
	int_playerUnitNumber = number;
	return;
}

void Player::setCurrentEnergieStorage(int energie)
{
	int_currentEnergieStorage = energie;
	return;
}

QString Player::getPlayerName() const	
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

int Player::getCurrentEnergieStorage() const
{
	return int_currentEnergieStorage;
}