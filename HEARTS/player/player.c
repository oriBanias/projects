#include "../../../DS/sorts/insertion/insertion.h"
#include "../include/player.h"
#include <stdio.h>
#include <string.h>
#include "../include/card.h"
#include "../include/ui.h"

#define NAME_LENGTH 32

struct Player
{
	char m_name[NAME_LENGTH];
	Table* suitArr[C_NUM_OF_SUITS];
	PlayerType 	m_playerType;
	int m_score;
};
/*
static int Is2Club(Vector_int* _suitArr)
{

}  return 0 as false or 1 for true if the player has the card
*/
Player* PlayerCreate(char* _name, PlayerType _playerType)
{
	int i = 0;
	Player* newPlayer = (Player*)malloc(sizeof(Player));
	if (newPlayer == NULL)
	{
		return NULL;
	}
	
	for(i=0; i < C_NUM_OF_SUITS; ++i)
	{
		newPlayer->suitArr[i] = VectorCreate(C_NUM_OF_RANKS, 0);
	}
	
	newPlayer->m_playerType = _playerType;
	strcpy(newPlayer->m_name, _name);
	newPlayer->m_score = 0;
	return newPlayer;
	
}

void PlayerDestroy(Player* _player)
{
	int i;
	if (_player == NULL)
	{
		return;
	}

	for(i = 0; i < C_NUM_OF_SUITS; ++i)
	{
		VectorDestroy(_player->suitArr[i]);
	}
	
	free(_player);
	return;
}

void PlayerDropToTable(Player* _player, Table* _table) 
{
	size_t numItems;
	int item;
	Suit suitFirst;
	int i = 0;
	
	VectorGetItemsNum(_table, &numItems);
	if(numItems == 0)
	{
			while(i < C_NUM_OF_SUITS)
			{
				VectorGetItemsNum(_player->suitArr[i], &numItems);
				if(numItems != 0 )
				{
					VectorDelete(_player->suitArr[i], &item); 
					VectorAdd(_table, item);
					return;	
				}
				++i;
		    }
	}
	else
	{
		VectorGet(_table, 1, &item);
		suitFirst = GetSuit(item);
		VectorGetItemsNum(_player->suitArr[suitFirst], &numItems);
		if(0 == numItems)
		{
			for(i = 0; i < C_NUM_OF_SUITS; ++i)
			{
				VectorGetItemsNum(_player->suitArr[i], &numItems);
				if(numItems != 0)
				{
					VectorDelete(_player->suitArr[i], &item); 
					VectorAdd(_table, item);
					return;
				}
			}
		}
		
		else
		{
			VectorDelete(_player->suitArr[suitFirst], &item);
			VectorAdd(_table, item);
		}
	}
} 

/*void PlayerTransfer3Cards(Player* _player)
{

}
*/

void PlayerAddCard(Player* _player, int _card)
{
	Suit curSuit;
	curSuit = GetSuit(_card);
	VectorAdd(_player->suitArr[curSuit], _card);
	InsertionSort(_player->suitArr[curSuit]);
}

const char* PlayerGetName(Player* _player)
{
	return _player->m_name;	
}

int PlayerDoYouHaveCard(Player* _player, int _card)
{
	size_t itemNum;
	size_t i;
	Suit curSuit;
	int searchCard;
	curSuit = GetSuit(_card);
	
	VectorGetItemsNum(_player->suitArr[curSuit], &itemNum);
	
	if(itemNum == 0)
	{
		return 0;
	}
	
	for(i = 1; i <= itemNum; ++i)
	{
		VectorGet(_player->suitArr[curSuit], i, &searchCard);
		if (searchCard == _card)
		{
			return 1;
		}
	}
	return 0;
}

int PlayerGetScore(Player* _player)
{
	return _player->m_score;
}

void PlayerAddScore(Player* _player,int _score)
{
	if (_player != NULL)
	{
		_player->m_score += _score;
	}
}

void PlayerShowName(Player* _player)
{
	DisplayMessage(PlayerGetName(_player));
}

void PlayerShowCards(Player* _player)
{
	int i=0;
	for (i=0; i<C_NUM_OF_SUITS; ++i)
	{ 
		PrintCards(_player->suitArr[i]);
	}	
}

void PlayerShowScore(Player* _player)
{
	PlayerShowName(_player);
	PrintScore(PlayerGetScore(_player));
}

void PlayerShowWinner(Player* _player)
{
	DisplayMessage("The Winner is: \n");
	PlayerShowName(_player);
	PlayerShowScore(_player);
}

