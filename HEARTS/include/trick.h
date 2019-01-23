#ifndef __TRICK_H__
#define __TRICK_H__
#include "player.h"
#include "../../../DS/vector/vector.h"

typedef struct Trick Trick;

/*
	description:creating the trick struct
	input: size of struct trick
	return value: pointer to the trick we have created			
*/
Trick* TrickCreate(Player* _players[], int _starter);

/*
	description:destroying the trick struct we have created
	input: pointer to the trick we have created
	return value: none			
*/
void TrickDestroy(Trick* _trick);

/*
	description:set the loser of the last trick
	input: index of the card that looses in the trick
	return value: pointer to the player that been the loser			
*/
int TrickGetLoser(Trick* _trick);

/*
	description:activate functions in order to run a trick 13 times each round
	input: none
	return value: none			
*/
void TrickRun(Trick* _trick);

/*
	description:get the loser score of the last trick
	input: pointer to the trick
	return value: num of points in trick
*/
int TrickGetScore(Trick* _trick);

void ShowTable(Trick* _trick);

#endif
