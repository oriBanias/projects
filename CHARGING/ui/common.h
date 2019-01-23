#ifndef __COMMON_H__
#define __COMMON_H__

#define BUFFER_SIZE 512
#define THREAD_NUM 5

typedef struct Msg
{
	long m_type;
	char m_text[BUFFER_SIZE];
}Msg;

static const int g_msgTextLength = BUFFER_SIZE * sizeof(char);

#endif
