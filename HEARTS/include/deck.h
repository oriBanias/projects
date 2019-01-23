#ifndef __DECK_H__
#define __DECK_H__

typedef struct Deck Deck;

/*
	description: shufffle randomly the cards of the deck 
	input: pointer of the deck struct we have created
	return value: none		
*/
void DeckShuffle(Deck* _deck);

/*
	description: creating the deck that holds the 52 indexes of cards
	input: none
	return value: pointer to the deck we have created		
*/
Deck* DeckCreate(void);

/*
	description: destroying the deck we created 
	input: pointer to the deck we have created	
	return value: none		
*/
void DeckDestroy(Deck* _deck);

/*
	description: dealing 1 card to each player  
	input: pointer to deck struct we have created	
	return value: index of card		
*/
int DeckDealCard(Deck* _deck);

/*
	description: printing the deck  
	input: pointer to deck struct we have created	
	return value: none	
*/
void DeckPrint(Deck* _deck);

#endif
