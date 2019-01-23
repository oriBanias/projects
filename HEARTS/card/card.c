#include "../include/card.h"
#include "../../../DS/vector/vector.h"
#include <assert.h>

struct Card
{
	int Suit;
	int Rank;
};		

static const Card g_cards[]={

	{C_SPADE, C_TWO},
	{C_SPADE, C_THREE },
	{C_SPADE, C_FOUR},
	{C_SPADE, C_FIVE},
	{C_SPADE, C_SIX},
	{C_SPADE, C_SEVEN},
	{C_SPADE, C_EIGHT},
	{C_SPADE, C_NINE},
	{C_SPADE, C_TEN},
	{C_SPADE, C_PRINCE},
	{C_SPADE, C_QUEEN},
	{C_SPADE, C_KING},
	{C_SPADE, C_ACE},

	{C_DIAMOND, C_TWO},
	{C_DIAMOND, C_THREE},
	{C_DIAMOND, C_FOUR},
	{C_DIAMOND, C_FIVE},
	{C_DIAMOND, C_SIX},
	{C_DIAMOND, C_SEVEN},
	{C_DIAMOND, C_EIGHT},
	{C_DIAMOND, C_NINE},
	{C_DIAMOND, C_TEN},
	{C_DIAMOND, C_PRINCE},
	{C_DIAMOND, C_QUEEN},
	{C_DIAMOND, C_KING},
	{C_DIAMOND, C_ACE},

	{C_CLUB, C_TWO},
	{C_CLUB, C_THREE },
	{C_CLUB, C_FOUR},
	{C_CLUB, C_FIVE},
	{C_CLUB, C_SIX},
	{C_CLUB, C_SEVEN},
	{C_CLUB, C_EIGHT},
	{C_CLUB, C_NINE},
	{C_CLUB, C_TEN},
	{C_CLUB, C_PRINCE},
	{C_CLUB, C_QUEEN},
	{C_CLUB, C_KING},
	{C_CLUB, C_ACE},

	{C_HEART, C_TWO},
	{C_HEART, C_THREE },
	{C_HEART, C_FOUR},
	{C_HEART, C_FIVE},
	{C_HEART, C_SIX},
	{C_HEART, C_SEVEN},
	{C_HEART, C_EIGHT},
	{C_HEART, C_NINE},
	{C_HEART, C_TEN},
	{C_HEART, C_PRINCE},
	{C_HEART, C_QUEEN},
	{C_HEART, C_KING},
	{C_HEART, C_ACE}
};

Rank GetRank(int _id)
{
	assert(_id >= 0 && _id < NUM_OF_CARDS);
	return g_cards[_id].Rank;
}

Suit GetSuit(int _id)
{
	
	assert(_id >= 0 && _id < NUM_OF_CARDS);
	return g_cards[_id].Suit;
}

int GetCardId(Rank _rank, Suit _suit)
{
	return (int)(C_NUM_OF_RANKS * _suit + _rank);
}

