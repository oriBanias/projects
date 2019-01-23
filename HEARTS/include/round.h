#ifndef __ROUND_H__
#define __ROUND_H__
#include "../include/player.h"

typedef enum
{
	DIR_NONE,
	DIR_LEFT,
	DIR_ACROSS,
	DIR_RIGHT
} Direction;

typedef struct Round Round;

/*
	description: activate all the functions that responsible to run the round 
	input: none
	return value: none		
*/
int RoundRun(Round* _round);

/*
	description: creating a struct round  
	input: the size of the struct
	return value: pointer to the stuct round we have created		
*/
Round* RoundCreate(Player** _players, Direction _direction);


/*
	description: destroying a struct round  
	input:pointer to the stuct round we have created	
	return value: none	
*/
void RoundDestroy(Round* _round);


void RoundShowScore(Round *_round);

#endif


