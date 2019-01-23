#include "../include/trick.h"
#include "../include/card.h"
#include "../include/ui.h"



struct Trick
{
	Table* table;
	Player* m_players[4];
	int m_starter;
}; 

void ShowTable(Trick* _trick)
{
	DisplayMessage("\nThe current table is:");
	PrintCards(_trick->table);
}

Trick* TrickCreate(Player* _players[], int _starter)
{
	int i;
	Trick* trick = (Trick*)malloc(sizeof(Trick));
	
	if (trick == NULL)
	{
		return NULL;
	} 	
	
	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		trick->m_players[i] = _players[i];
	}
	trick->table = VectorCreate(C_NUM_OF_SUITS, 0);
	trick->m_starter = _starter;
	
	return trick;
}

void TrickDestroy(Trick* _trick)
{
	if (_trick == NULL)
	{
		return;
	}
	
	VectorDestroy(_trick->table);
	free(_trick);
	return;
}

int TrickGetLoser(Trick* _trick)
{
	int maxCardRank;
	int maxCardSuit;
	int looserCardIndx = _trick->m_starter;
	size_t indx = 1;
	int checkedCard;

	VectorGet(_trick->table, indx, &checkedCard);
	maxCardSuit = GetSuit(checkedCard);
	maxCardRank = GetRank(checkedCard);

	for (indx = 2; indx <= C_NUM_OF_SUITS; ++indx)
	{	
		VectorGet(_trick->table, indx, &checkedCard);

		if (maxCardSuit == GetSuit(checkedCard) && maxCardRank < GetRank(checkedCard))
		{
			looserCardIndx = (int)indx-1;
		}
	}

	looserCardIndx = (_trick->m_starter + looserCardIndx) % NUM_OF_PLAYERS;  /* to check if m_starter needed instead of looser to indicate the looser for next trick */

	return looserCardIndx;
}
int TrickGetScore(Trick* _trick)
{
	size_t i;
	int item;
	int points = 0;
	for (i = 1; i <= C_NUM_OF_SUITS; ++i)
	{
		VectorGet(_trick->table, i, &item);
		if (GetSuit(item) == 3)
		{
			++points;
		}
		else if (GetSuit(item) == C_SPADE && GetRank(item) == C_QUEEN)
		{
			points+=13;
		}
	}
	return points;
}

void TrickRun(Trick* _trick)
{
	int i = 0;

	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		PlayerDropToTable(_trick->m_players[(_trick->m_starter + i +1) % NUM_OF_PLAYERS], _trick->table);
	}
	ShowTable(_trick);
} 
