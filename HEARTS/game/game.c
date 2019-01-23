#include "../include/game.h"
#include "../include/card.h"
#include "../include/game.h"
#include "../include/round.h"
#include "../include/ui.h"
#include "../include/trick.h"
#include "../include/deck.h"
#include "../include/card.h"
#include "../../../DS/vector/vector.h"


struct Game
{
	int roundNum;
	Player** competitor;
	Round* round;
};


Game* GameCreate()
{
	int i = 0;
	char* name = NULL;
	int type = 0;
	Game* game = (Game*)malloc(sizeof(Game));
	
	if (game != NULL)
	{
		game->roundNum = 0;
		game->competitor = (Player**)malloc(sizeof(Player*) * NUM_OF_PLAYERS);
		
		if ((game->competitor != NULL))
		{
			for (i=0; i<NUM_OF_PLAYERS; ++i)
			{
				name = GetUserName();
				type = GetUserType();
				game->competitor[i] = PlayerCreate(name, type);
				free(name);
			}
			
			game->round = RoundCreate(game->competitor, DIR_LEFT);
		}
	}
	
	return game;
}

void GameRun()
{
	int gameOverCheck = -1;
	Game* game = GameCreate();
	while(gameOverCheck == -1)
	{	
		gameOverCheck = RoundRun(game->round);
		++game->roundNum;
	}
	GameFindWinners(game);
	GameDestroy(game);
}

void GameDestroy(Game* _game)
{
	int i = 0;
	if (_game == NULL)
	{
		return;
	}
	RoundDestroy(_game->round);

	for (i=0; i<NUM_OF_PLAYERS; ++i)
	{
	 	if (_game->competitor[i] != NULL)
	 	{
			PlayerDestroy(_game->competitor[i]);
		}	
	}
	free(_game->competitor);
	free(_game);
}

void GameFindWinners(Game* _game)
{
	int i=0;
	Player* winnerPlayer = NULL;
	
	if (_game != NULL)
	{
		/* Get minimum score player */
		winnerPlayer = _game->competitor[0];
		for (i=1; i<NUM_OF_PLAYERS; ++i)
		{
			if (PlayerGetScore(_game->competitor[i]) < PlayerGetScore(winnerPlayer))
			{
				winnerPlayer = _game->competitor[i];
			}
		}
		PlayerShowWinner(winnerPlayer);
	}
}
