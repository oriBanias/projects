#ifndef __UI_H__
#define __UI_H__
#include "../../../DS/vector/vector.h" 

void DisplayMessage(const char* msg, ...);

void PrintCards(Vector_int* _cardArr);

void PrintCard(int _card);

int GetUserType(void);

char* GetUserName(void);	

void PrintScore(int _score);

#endif
