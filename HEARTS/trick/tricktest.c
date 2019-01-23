#include "../mu_test.h"
#include "../include/trick.h"
#include "../include/ui.h"
#include "../include/card.h"
#include "../include/deck.h"
#include "../../../DS/vector/vector.h"
#include <stdio.h>

/********* TRICK CREATE ***********/
UNIT(creating_normal_trick)

	int starter = 0;
	int index;
	Trick* trick = NULL;
	const char* name1 = "ori";
	const char* name2 = "kfir";
	const char* name3 = "moshe";
	const char* name4 = "tomer";
	Player* arr[4];
	PlayerType type1 = PT_HUMAN;
	PlayerType type2 = PT_COMPUTER;
	arr[0] = PlayerCreate(name1, type1);
	arr[1] = PlayerCreate(name2, type2);
	arr[2] = PlayerCreate(name3, type2);
	arr[3] = PlayerCreate(name4, type2);
	trick = TrickCreate(arr, starter);
	ASSERT_THAT(trick != NULL);
	for(index = 0 ; index < 4 ; ++index)
    {
        PlayerDestroy(arr[index]);
    }
	TrickDestroy(trick);
END_UNIT

/********* TRICK GET LOSER ***********/
UNIT(get_loser_trick)
	int starter = 0;
	int index = 0;
	int i;
	int curScore;
	Trick* trick = NULL;
	Deck* deck = NULL;
	int card;
	const char* name1 = "ori";
	const char* name2 = "kfir";
	const char* name3 = "moshe";
	const char* name4 = "tomer";
	Player* arr[4];
	PlayerType type1 = PT_HUMAN;
	PlayerType type2 = PT_COMPUTER;

 	arr[0] = PlayerCreate(name1, type1);
	arr[1] = PlayerCreate(name2, type2);
	arr[2] = PlayerCreate(name3, type2);
	arr[3] = PlayerCreate(name4, type2);

	deck = DeckCreate();
	DeckShuffle(deck);

	for (i = 0; i < NUM_OF_CARDS/NUM_OF_PLAYERS; ++i)
	{
		card = DeckDealCard(deck);
		PlayerAddCard(arr[0], card);

		card = DeckDealCard(deck);
		PlayerAddCard(arr[1], card);

		card = DeckDealCard(deck);
		PlayerAddCard(arr[2], card);

		card = DeckDealCard(deck);
		PlayerAddCard(arr[3], card);
	}
	
	trick = TrickCreate(arr, starter);
	TrickRun(trick);
	curScore = TrickGetScore(trick);
	printf("the score is: %d \n", curScore);
	printf("the loser is: %d\n", TrickGetLoser(trick));

	ASSERT_THAT(TrickGetLoser(trick) == 3);

	for(index = 0 ; index < NUM_OF_PLAYERS ; ++index)
    {
        PlayerDestroy(arr[index]);
    }
	TrickDestroy(trick);
	
END_UNIT

/********* TRICK GET LOSER ***********/
UNIT(get_loser_trick2)
	int starter = 0;
	int index = 0;
	int i;
	int curScore;
	Trick* trick = NULL;
	Deck* deck = NULL;
	int card;
	const char* name1 = "ori";
	const char* name2 = "kfir";
	const char* name3 = "moshe";
	const char* name4 = "tomer";
	Player* arr[4];
	PlayerType type1 = PT_HUMAN;
	PlayerType type2 = PT_COMPUTER;

 	arr[0] = PlayerCreate(name1, type1);
	arr[1] = PlayerCreate(name2, type2);
	arr[2] = PlayerCreate(name3, type2);
	arr[3] = PlayerCreate(name4, type2);

	deck = DeckCreate();
	DeckShuffle(deck);

	for (i = 0; i < NUM_OF_CARDS/NUM_OF_PLAYERS; ++i)
	{
		card = DeckDealCard(deck);
		PlayerAddCard(arr[0], card);

		card = DeckDealCard(deck);
		PlayerAddCard(arr[1], card);

		card = DeckDealCard(deck);
		PlayerAddCard(arr[2], card);

		card = DeckDealCard(deck);
		PlayerAddCard(arr[3], card);
	}
	
	trick = TrickCreate(arr, starter);
	TrickRun(trick);
	curScore = TrickGetScore(trick);
	printf("the score is: %d \n", curScore);
	printf("the loser is: %d\n", TrickGetLoser(trick));

	ASSERT_THAT(TrickGetLoser(trick) == 0);

	for(index = 0 ; index < NUM_OF_PLAYERS ; ++index)
    {
        PlayerDestroy(arr[index]);
    }
	TrickDestroy(trick);
	
END_UNIT


TEST_SUITE(player)

TEST(creating_normal_trick)
TEST(get_loser_trick)
TEST(get_loser_trick2)


END_SUITE
