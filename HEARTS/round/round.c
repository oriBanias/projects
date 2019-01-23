#include "../include/round.h"
#include "../include/trick.h"
#include "../include/deck.h"
#include "../include/card.h"
#include "../include/ui.h"
#include "../../../DS/vector/vector.h"

struct Round
{
	Player** players;
	Direction m_dir;
};

Round* RoundCreate(Player** _players, Direction _direction)
{
	Round* round = (Round*)malloc(sizeof(Round));
	
	if (round == NULL)
	{
		return NULL;
	}
	
	round->m_dir = _direction;
	round->players = _players;
	return round;	
}

void RoundDestroy(Round* _round)
{
	if (_round != NULL)
	{
		free(_round);
	}
}

int IsGameOver(Round* _round)
{
	int i = 0;
	for (i=0; i<NUM_OF_PLAYERS; ++i)
	{
		if (PlayerGetScore(_round->players[i]) >= 100)
		{
			return i;
		} 
	}
	return -1;
}

int RoundRun(Round* _round)
{
	Trick* trick = NULL;
	int card = 0;
	int i = 0;
	int j = 0;
	int score = 0;
	int beginner = 0;
	Deck* deck = DeckCreate();
	if (deck != NULL)
	{
		DeckShuffle(deck);
		for (i = 0; i < NUM_OF_CARDS/NUM_OF_PLAYERS; ++i )
		{
			for (j = 0; j < NUM_OF_PLAYERS; ++j)
			{
				card = DeckDealCard(deck);
				PlayerAddCard(_round->players[j], card);
			}
		}
		for (i = 0; i < NUM_OF_PLAYERS; ++i)
		{
			PlayerShowName(_round->players[i]);
			PlayerShowCards(_round->players[i]);
		}
		
		for(i = 0; i < NUM_OF_CARDS/NUM_OF_PLAYERS; ++i)
		{
			trick = TrickCreate(_round->players, beginner);
			if (trick != NULL)
			{
				TrickRun(trick);
				beginner = TrickGetLoser(trick);
				score = TrickGetScore(trick);
				PlayerAddScore(_round->players[beginner], score);
				TrickDestroy(trick);
			}
		}
		RoundShowScore(_round);
		DeckDestroy(deck);
	}
	return IsGameOver(_round);
}

void RoundShowScore(Round *_round)
{
	int i = 0;
	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		PlayerShowScore(_round->players[i]);
	}
}


