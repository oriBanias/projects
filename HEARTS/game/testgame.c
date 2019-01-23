#include "../mu_test.h"
#include "../../../DS/vector/vector.h"
#include "../include/round.h"
#include "../include/trick.h"
#include "../include/deck.h"
#include "../include/player.h"
#include "../include/card.h"
#include "../include/game.h"
#include <stdio.h>



/********* GAME RUN ***********/
UNIT(running_normal_game)
	GameRun();
END_UNIT


TEST_SUITE(player)

TEST(running_normal_game)

END_SUITE	
