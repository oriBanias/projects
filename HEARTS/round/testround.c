#include "../mu_test.h"
#include "../../../DS/vector/vector.h"
#include "../include/round.h"
#include "../include/trick.h"
#include "../include/deck.h"
#include "../include/player.h"
#include "../include/card.h"
#include <stdio.h>

/********* ROUND RUN ***********/
UNIT(running_normal_round)
	Round* round;
	Player* players[4];
	players[0] = PlayerCreate("ori", PT_HUMAN);
	players[1] = PlayerCreate("yafit", PT_COMPUTER);
	players[2] = PlayerCreate("mama", PT_COMPUTER);
	players[3] = PlayerCreate("eli", PT_COMPUTER);
	round = RoundCreate(players, DIR_LEFT);
	ASSERT_THAT(round != NULL);
	RoundRun(round);
	PlayerDestroy(players[0]);
	PlayerDestroy(players[1]);
	PlayerDestroy(players[2]);
	PlayerDestroy(players[3]);
	RoundDestroy(round);
END_UNIT

/********* ROUND CREATE ***********/
UNIT(creating_normal_round)
	Round* round;
	Player* players[4];
	players[0] = PlayerCreate("ori", PT_HUMAN);
	players[1] = PlayerCreate("yafit", PT_COMPUTER);
	players[2] = PlayerCreate("mama", PT_COMPUTER);
	players[3] = PlayerCreate("eli", PT_COMPUTER);
	round = RoundCreate(players, DIR_LEFT);
	ASSERT_THAT(round != NULL);
	PlayerDestroy(players[0]);
	PlayerDestroy(players[1]);
	PlayerDestroy(players[2]);
	PlayerDestroy(players[3]);
	RoundDestroy(round);
END_UNIT



TEST_SUITE(player)

TEST(creating_normal_round)
TEST(running_normal_round)

END_SUITE
