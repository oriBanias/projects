#include "../mu_test.h"
#include "../include/deck.h"
#include "../../../DS/vector/vector.h"
#include <stdio.h>

/********* DECK CREATE ***********/
UNIT(creating_normal_deck)

	Deck* deck = NULL;
	deck = DeckCreate();
	ASSERT_THAT(deck != NULL);
	DeckDestroy(deck);
END_UNIT

UNIT(cheking_DeckDealCards_function)

	int value;
	Deck* deck = NULL;
	deck = DeckCreate();
	value = DeckDealCard(deck);
	ASSERT_THAT(-1 != value);
	DeckDestroy(deck);

END_UNIT

UNIT(cheking_DeckShuffle_function)

	Deck* deck = NULL;
	deck = DeckCreate();
	DeckPrint(deck);
	DeckShuffle(deck);
	DeckPrint(deck); 
	ASSERT_THAT(NULL != deck);
	DeckDestroy(deck);

END_UNIT


TEST_SUITE(card)

TEST(creating_normal_deck)
TEST(cheking_DeckDealCards_function)
TEST(cheking_DeckShuffle_function)

END_SUITE
