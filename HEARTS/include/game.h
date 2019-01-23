#ifndef __GAME_H__
#define __GAME_H__
#include "../include/player.h"

typedef struct Game Game;


/*
	description: activate all the functions that responsible to run the game 
	input: none
	return value: none		
*/
void GameRun();

/*
	description: creating a struct game  
	input: the size of the struct
	return value: pointer to the stuct game we have created		
*/
Game* GameCreate();


/*
	description: destroying a struct game  
	input:pointer to the stuct game we have created	
	return value: none	
*/
void GameDestroy(Game* _game);

void GameFindWinners(Game* _game);
#endif
