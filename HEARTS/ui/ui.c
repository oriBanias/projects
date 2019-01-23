#include "../include/ui.h"
#include "../include/round.h"
#include "../include/trick.h"
#include "../include/deck.h"
#include "../include/player.h"
#include "../include/card.h"
#include "../include/game.h"
#include <stdarg.h>
#include <string.h>


/* bold/not bold */
#define BOLD_ON         "\x1b[1m"
#define BOLD_OFF        "\x1b[21m"

/* colors */
#define NORMAL          "\x1B[0m"
#define BLACK           "\x1b[30m"
#define RED             "\x1B[31m"
#define GREEN           "\x1B[32m"
#define YELLOW          "\x1B[33m"
#define BLUE            "\x1B[34m"
#define MAGENTA         "\x1B[35m"
#define CYAN            "\x1B[36m"
#define WHITE           "\x1B[37m"
#define GRAY            "\x1b[90m"

/* cards suites symbols */
#define HEART           "\xE2\x99\xA5"
#define SPADE           "\xE2\x99\xA0"
#define DIAMOND         "\xE2\x99\xA6"
#define CLUB            "\xE2\x99\xA3"

/**** Usage examples: ****/

void PrintCard(int _card)
{
    if(_card == -1)
    {
        return;
    }
    else
    {
        switch (GetSuit(_card))
        {
            case C_HEART:
                printf(RED HEART NORMAL " ");
                break;
            case C_DIAMOND:
                printf(RED DIAMOND NORMAL " ");
                break;
            case C_CLUB:
                printf(GREEN CLUB NORMAL " ");
                break;
            case C_SPADE:
                printf(GREEN SPADE NORMAL " ");
                break;
            default:
                break;                
        }        switch (GetRank(_card))
        {
            case C_TWO:
                printf(BOLD_ON "2  " BOLD_OFF);
                break;
            case C_THREE:
                printf(BOLD_ON "3  " BOLD_OFF);
                break;
            case C_FOUR:
                printf(BOLD_ON "4  " BOLD_OFF);
                break;
            case C_FIVE:
                printf(BOLD_ON "5  " BOLD_OFF);
                break;
            case C_SIX:
                printf(BOLD_ON "6  " BOLD_OFF);
                break;
            case C_SEVEN:
                printf(BOLD_ON "7  " BOLD_OFF);
                break;
            case C_EIGHT:
                printf(BOLD_ON "8  " BOLD_OFF);
                break;
            case C_NINE:
                printf(BOLD_ON "9  " BOLD_OFF);
                break;
            case C_TEN:
                printf(BOLD_ON "10 " BOLD_OFF);
                break;
            case C_PRINCE:
                printf(BOLD_ON "J  " BOLD_OFF);
                break;                                    
            case C_QUEEN:
                printf(BOLD_ON "Q  " BOLD_OFF);
                break;
            case C_KING:
                printf(BOLD_ON "K  " BOLD_OFF);
                break;
            case C_ACE:
                printf(BOLD_ON "A  " BOLD_OFF);
                break;                                
            default:
                break;
        }
    }
        
}

void PrintCards(Vector_int* _cardArr)
{
    int card;
    size_t index , numOfItems;
    
    VectorGetItemsNum(_cardArr , &numOfItems);
    
    printf("\n");
    for(index = 1 ; index <= numOfItems ; ++index)
    {
        VectorGet(_cardArr , index , &card);
        PrintCard(card);
    }
    
}

void PrintScore(int _score)
{
	printf("\tThe score is: %d\n", _score);
}

void DisplayMessage(const char* msg, ...)
{
  va_list args;   va_start(args, msg);
  printf("\n");
  vprintf(msg, args);
  va_end(args);
}

char* GetUserName(void)
{
	
	char* name = (char*)malloc(sizeof(char)*20);
	printf ("please enter your name:\n");
	scanf("%s", name); 
	
	return name;
}

int GetUserType(void)
{
	int type = 0;
	printf("please enter your type: (0 = computer  1 = human)\n");
	scanf("%d", &type);
	return type;
}






