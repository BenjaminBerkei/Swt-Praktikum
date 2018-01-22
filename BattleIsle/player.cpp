/*
 * Author: Miguel
 * Version: 0.3
 * Datum 03.01.2018
 * */
/* Author: Lucas
 * Version: 0.4
 * Datum 14.01.20118
 * Kommentare: bool für HQ destroyed eingefügt, increase-/decreaseUnitNumber() Hilfsfunktionen geschrieben
 * */
#include "player.h"


Player::Player(QString playerName,int id, bool ki, int totalEnergie, int currentEnergie, int unitNumber, int playerScore)
    :str_playerName(playerName), int_playerID(id), int_playerScore(playerScore), int_playerTotalEnergie(totalEnergie),
      int_currentEnergieStorage(currentEnergie), int_playerUnitNumber(unitNumber), bool_HQDestroyed(false), bool_isKI(ki) {}

Player::~Player(){
	/*
	 * Delete nur wenn du mit new speicher allociert hast
	 */
    return;
}

void Player::increaseUnitNumber()
{
    int_playerUnitNumber++;
}

void Player::decreaseUnitNumber()
{
    int_playerUnitNumber--;
}

void Player::serialize(QTextStream& out)
{
    out << int_playerID << " " << str_playerName << " " << int_playerScore << " "
        << int_currentEnergieStorage;
    if(bool_isKI == true)
    {
        out << " " << 1;
    }else{
        out << " " << 0;
    }
    out << "\n";

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
    if(int_playerTotalEnergie < int_currentEnergieStorage)
    {
        int_playerTotalEnergie = int_currentEnergieStorage;
    }
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
    return int_playerTotalEnergie;
}

int Player::getPlayerUnitNumber() const
{
	return int_playerUnitNumber;
}

int Player::getCurrentEnergieStorage() const
{
	return int_currentEnergieStorage;
}

int Player::getPlayerID() const
{
    return int_playerID;
}

bool Player::getHQDestroyed() const
{
    return bool_HQDestroyed;
}

void Player::setHQDestroyed(bool value)
{
    bool_HQDestroyed = value;
}
