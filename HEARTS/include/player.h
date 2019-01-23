#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "../../../DS/vector/vector.h"

typedef struct Player Player;
typedef Vector_int Table;

typedef enum
{
	PT_COMPUTER,
	PT_HUMAN
} PlayerType;

/*
	description: creating struct of player
	input: string - name of the player, the type of the player - computer or human
	return value: pointer to the player struct we created 
*/
Player* PlayerCreate(char* _name, PlayerType _playerType);

/*
	description: destroying the struct of player we created
	input: pointer to the player struct we wish to destroy
	return value: none		
*/
void PlayerDestroy(Player* _player);

/*
	description: the player drop one card that he chooses into the table
	input: pointer to the table that holds 4 cards and pointer to the player that needs to drop the card
	return value: none		
*/
void PlayerDropToTable(Player* _player, Table* table);

/*
	description: transfering a card to an array that holde the 12 cards of the 4 players
	input: pointer to the player, pointer to the cards we wish to transfer, the number of cards we wish to transfer
	return value: none		
*/
void PlayerTransferCards(Player* _player, int* _thrownCards, int _numOfCards);

/*
	description: adding card to a player
	input: pointer to the player and the card we want to add to the player
	return value: none		
*/
void PlayerAddCard(Player* _player, int _card);

/*
	description: asking the player for his name
	input: pointer to the player and the card we want to add to the player
	return value: none		
*/
const char* PlayerGetName(Player* _player);

/*
	description: asking the player if he has a card of the suit on the table.
	input: pointer to the player we would like to check and the card of the first player.
	return value: 0 for false, 1 for true		
*/
int PlayerDoYouHaveCard(Player* _player, int _card);

/* TODO:!!!!
*/
int PlayerGetScore(Player* _player);
void PlayerAddScore(Player* _player,int _score);
void PlayerShowWinner(Player* _player);

/* UI for show player detailes... */
void PlayerShowName(Player* _player);
void PlayerShowCards(Player* _player);
void PlayerShowScore(Player* _player);

#endif
