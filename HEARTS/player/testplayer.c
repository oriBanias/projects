#include "../mu_test.h"
#include "../include/player.h"
#include "../../../DS/vector/vector.h"
#include <stdio.h>

/********* PLAYER CREATE ***********/
UNIT(creating_normal_player)

	const char* name = "ori";
	Player* player = NULL;
	player = PlayerCreate(name, PT_HUMAN);
	ASSERT_THAT(player != NULL);
	PlayerDestroy(player);
END_UNIT

/********* PLAYER GET NAME ***********/
UNIT(getting_player_name)

	const char* name = "ori";
	Player* player = NULL;
	player = PlayerCreate(name, PT_HUMAN);
	ASSERT_THAT(0 == strcmp("ori", PlayerGetName(player)));
	PlayerDestroy(player);
END_UNIT

/********* PLAYER ADDING CARD ***********/
UNIT(player_add_card)
	
	const char* name = "ori";
	Player* player = NULL;
	player = PlayerCreate(name, PT_HUMAN);
	PlayerAddCard(player, 2);
	ASSERT_THAT(1 == PlayerDoYouHaveCard(player, 2));
	PlayerDestroy(player);
END_UNIT

/********* PLAYER HAVE A CARD ***********/
UNIT(player_have_a_card)
	
	const char* name = "ori";
	Player* player = NULL;
	player = PlayerCreate(name, PT_HUMAN);
	PlayerAddCard(player, 2);
	ASSERT_THAT(0 == PlayerDoYouHaveCard(player, 3));
	PlayerDestroy(player);
END_UNIT

/********* PLAYER DROP TO TABLE ***********/
UNIT(player_drop_to_table)
	
	const char* name = "ori";
	Player* player = NULL;
	Vector_int* table;
	table = VectorCreate(4, 0);
	player = PlayerCreate(name, PT_HUMAN);
	PlayerAddCard(player, 2);
	PlayerAddCard(player, 5);
	PlayerAddCard(player, 3);
	PlayerAddCard(player, 14);
	PlayerDropToTable(player, table);
	PlayerDropToTable(player, table);
	PlayerDropToTable(player, table);
	PlayerDropToTable(player, table);
	ASSERT_THAT(0 == PlayerDoYouHaveCard(player, 5));
	ASSERT_THAT(0 == PlayerDoYouHaveCard(player, 3));
	ASSERT_THAT(0 == PlayerDoYouHaveCard(player, 2));
	ASSERT_THAT(0 == PlayerDoYouHaveCard(player, 14));
	VectorPrint(table);
	PlayerDestroy(player);
END_UNIT
/*
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
*/

TEST_SUITE(player)

TEST(creating_normal_player)
TEST(getting_player_name)
TEST(player_add_card)
TEST(player_have_a_card)
TEST(player_drop_to_table)

END_SUITE
