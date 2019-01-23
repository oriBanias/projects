#include "../include/deck.h"
#include "../../../DS/vector/vector.h"
#include "../include/card.h"
#include <time.h> /*for the rand function*/

struct Deck
{
	Vector_int* m_VecDeck;
	
};

static void Swap(Deck* _deck, size_t _a, size_t _b)
{
	int firstVal;
	int secondVal;
	VectorGet(_deck->m_VecDeck, _a, &firstVal);
	VectorGet(_deck->m_VecDeck, _b, &secondVal);
	VectorSet(_deck->m_VecDeck, _b, firstVal);
	VectorSet(_deck->m_VecDeck, _a, secondVal);
	
}

Deck* DeckCreate(void)
{
	int i;
	Deck* newDeck = (Deck*)malloc(sizeof(Deck));
	if (newDeck == NULL)
	{
		return NULL;
	}
	
	newDeck->m_VecDeck = VectorCreate(52, 0);
	
	for (i = 0; i < NUM_OF_CARDS; ++i)
	{
		VectorAdd(newDeck->m_VecDeck, i);
	}

	return newDeck;
}

void DeckDestroy(Deck* _deck)
{
	if (_deck == NULL)
	{
		return;
	}
	VectorDestroy(_deck->m_VecDeck);
	free(_deck);
	
}

void DeckShuffle(Deck* _deck)
{
	int index;
	size_t size = 0;
	time_t t;
	
	if (_deck == NULL)
	{
		return;
	}
	srand((unsigned) time(&t));
	VectorGetItemsNum(_deck->m_VecDeck, &size);
	for (index = (int)size; index >= 1; --index)
	{
		Swap(_deck, (size_t)rand() % ((size_t)index + 1) + 1, (size_t)index);
	}
	
}


int DeckDealCard(Deck* _deck)
{
	int cardVal;
	if (_deck == NULL)
	{
		return -1;
	}
	
	VectorDelete(_deck->m_VecDeck, &cardVal);

	return cardVal;
	
}

void DeckPrint(Deck* _deck)
{
	VectorPrint(_deck->m_VecDeck);
}
