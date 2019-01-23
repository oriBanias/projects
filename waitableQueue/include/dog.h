#ifndef __Dog_H__
#define __Dog_H__

#include "runnable.h"
#include <iostream>

class Dog : public Runnable
{
public:
	std::string m_name;		
	int m_id;
	int m_producerType;

public:
	Dog(int id, int type, int _souls = 9)

	:m_name("shoshi"), 
	m_id(id),
	m_producerType(type){}

	bool operator==(const Dog& _otherDog) const
	{
		return m_name == _otherDog.m_name;
	}
	
	virtual void run()
	{
		std::cout<<"Dog is nice"<<std::endl;
	}
};


#endif
