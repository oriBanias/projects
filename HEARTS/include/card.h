#ifndef __CARD_H__
#define __CARD_H__
#define NUM_OF_PLAYERS 4
typedef struct Card Card;

typedef enum Suit 
{
	C_SPADE,
	C_DIAMOND,
	C_CLUB,
	C_HEART,
	C_NUM_OF_SUITS
}Suit;

typedef enum Rank 
{
	C_TWO,
	C_THREE,
	C_FOUR,
	C_FIVE,
	C_SIX,
	C_SEVEN,
	C_EIGHT,
	C_NINE,
	C_TEN,
	C_PRINCE,
	C_QUEEN,
	C_KING,
	C_ACE,
	C_NUM_OF_RANKS
}Rank;

#define NUM_OF_CARDS (C_NUM_OF_RANKS * C_NUM_OF_SUITS) 
/* enum { NUM_OF_CARDS = (C_NUM_OF_RANKS * C_NUM_OF_SUITS) };*/

/*
	description: the function gets an index from deck, and return the rank of the card 
	input: the index of the card
	return value: type of rank of the specific card index- it returns to the deck		
*/
Rank GetRank(int _id);

/*
	description: the function gets an index from deck, and return the suit of the card 
	input: the index of the card
	return value:type of suit of the specific card index- it returns to the deck
*/
Suit GetSuit(int _id);

/*
	description:getting the rank and suit of the specific card and return the index of the card  
	input: rank and suit
	return value: card index		
*/
int GetCardId(Rank _rank, Suit _suit);






#endif
