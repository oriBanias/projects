#include "../mu_test.h"
#include "../include/card.h"
#include <stdio.h>

/********* CARD CHECK ***********/
UNIT(cheking_GetSuit_function)
	int spade_seven = 5;
	int diamond_prince = 20;
	int club_king = 34;
	int heart_ace = 51;
	ASSERT_THAT(GetSuit(spade_seven) == C_SPADE);
	ASSERT_THAT(GetSuit(diamond_prince) == C_DIAMOND);
	ASSERT_THAT(GetSuit(club_king) == C_CLUB);
	ASSERT_THAT(GetSuit(heart_ace) == C_HEART);
END_UNIT

UNIT(cheking_GetRank_function)
	int spade_seven = 5;
	int diamond_prince = 22;
	int club_king = 37;
	int heart_ace = 51;
	ASSERT_THAT(GetRank(spade_seven) == C_SEVEN);
	ASSERT_THAT(GetRank(diamond_prince) == C_PRINCE);
	ASSERT_THAT(GetRank(club_king) == C_KING);
	ASSERT_THAT(GetRank(heart_ace) == C_ACE);
END_UNIT

UNIT(cheking_GetCardId_function)
	
	ASSERT_THAT(GetCardId(C_SEVEN, C_SPADE) == 5);
	ASSERT_THAT(GetCardId(C_PRINCE, C_DIAMOND) == 22);
	ASSERT_THAT(GetCardId(C_KING, C_CLUB) == 37);
	ASSERT_THAT(GetCardId(C_ACE, C_HEART) == 51);
END_UNIT



TEST_SUITE(card)

TEST(cheking_GetSuit_function)
TEST(cheking_GetRank_function)
TEST(cheking_GetCardId_function)

END_SUITE
