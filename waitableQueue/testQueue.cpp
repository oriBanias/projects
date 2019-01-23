#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "queue.h"
#include "thread.h"
#include "mu_test.h"
#include "runnable.h"
#include "threadPool.h"


class Dog : public Runnable
{
public:
	Dog(int _souls = 9)
	:m_name("Kitten~ ")
	,m_souls(_souls)
	,m_result(_souls)
	{}
	
	virtual void run()
	{
		m_result *= m_souls;
	}
	
	bool operator==(const Dog& _otherDog) const
	{
		return m_souls == _otherDog.m_souls;
	}
	
	bool operator!=(const Dog& _otherDog) const
	{
		return m_souls != _otherDog.m_souls;
	}
	
	bool operator<=(const Dog& _otherDog) const
	{
		return m_souls <= _otherDog.m_souls;
	}
	
	//operator size_t() const { return m_souls; }
	operator int() const { return m_souls; }
	
	std::string m_name;	
	int m_souls;
	int m_result;
};

class Cat 
{
public:
	std::string m_name;		
	int m_id;
	int m_producerType;

public:
	Cat(int id, int type, int _souls = 9)

	:m_name("shoshi"), 
	m_id(id),
	m_producerType(type){}

	bool operator==(const Cat& _otherCat) const
	{
		return m_name == _otherCat.m_name;
	}
	
};

std::ostream& operator<<(std::ostream& _os , const Cat& _cat)
{
	_os << _cat.m_name;
	return _os;
}
/*
class TaskProducer : Runnable
{
	ThreadPool tp;
public:
	TaskProducer(ThreadPool& tp)
	: m_tp(tp)
	{}
	
	void run()
	{
		int n = 1000;
		while(--n)
		{
			Task t;
			tp.SubmitWork(new Task());
		}
	}
};
*/
class Producer : public Runnable, private UnCopyable
{
public:
	Producer(WaitableQueue<Cat>& que, int start, int end, int uType) :
	m_queue(que),
	rangeStart(start),
	rangeEnds(end),
	type(uType)
	{}
	
	virtual void run()
	{
		for(int i = rangeStart; i < rangeEnds; ++i)
		{
			m_queue.push(Cat(i, type));		
		}
	}
	 
private:
	WaitableQueue<Cat>& m_queue;	
public:
	int rangeStart;
	int rangeEnds;
	int type;
	
};



class Consumer : public Runnable, private UnCopyable
{
public:
	Consumer(WaitableQueue<Cat>& que, int n , int arrsize) 
	: m_queue(que),
	m_numOfIterations(n),
	m_arrSize(arrsize)
	{
		checkflg = true;
		m_sumArr = 0;
		try
		{
			m_arr = new int[m_arrSize];
			
		}
		catch(...)
		{
		
		}
		for (int i = 0; i < m_arrSize; ++i)
		{
			m_arr[i] = 0;
		}	
	}
	
	virtual ~Consumer()
	{
		delete[] m_arr;
	}

	virtual void run()
	{
		Cat tmp(-1,-1);		
		int prevId = -1;
		int prevType = 0;
		for(int i = 0; i < m_numOfIterations; ++i)
		{
			m_queue.pop(tmp);
			if((tmp.m_id <= prevId) && (tmp.m_producerType == prevType))
			{
				checkflg = false;
				break;
			}	
			prevId = tmp.m_id;
			prevType = tmp.m_producerType;
			++m_arr[tmp.m_id];
			++m_sumArr;
		}
	}
	 
	bool failed() 
	{ 
		return checkflg;
    }
    
public:
	int m_sumArr;
	
private:
	WaitableQueue<Cat>& m_queue;
	bool checkflg;
	int* m_arr;
	int m_numOfIterations;
	int m_arrSize;
};

/****************************** push and pop() ******************************/
UNIT(push)

	WaitableQueue<Cat> q;
	Consumer c(q, 10, 10);
	Producer p(q, 0, 10, 1);
	Thread t1(c);
	Thread t2(p);
/*
	t1.join();
	t2.join(); */

	ASSERT_THAT(  c.failed() );
	
END_UNIT


UNIT(check_if_fifo)

	WaitableQueue<Cat> wQueue;
	for(int  i = 0 ; i < 10 ; ++i)
	{
		wQueue.push(Cat(i, i));
	}

	Cat removed(-1, -1);
	for(int  i = 0; i < 10 ; ++i)
	{
		wQueue.pop(removed);
		ASSERT_THAT(removed.m_id == i);
	}

END_UNIT

UNIT(multiple_consumers_one_producers)

	WaitableQueue<Cat> q;
	Consumer c1(q, 600 , 1000);
	Consumer c2(q, 200 , 1000);
	Consumer c3(q, 200 , 1000);
	Producer p1(q, 0, 1000, 1);

	Thread t1(c1);
	Thread t2(c2);
	Thread t3(c3);
	Thread t4(p1);
/*
	t1.join();
	t2.join();
	t3.join();
	t4.join(); */

	std::cout<<"the sum is "<<(c1.m_sumArr+c2.m_sumArr+c3.m_sumArr)<<std::endl;
	ASSERT_THAT(  c1.failed() );
	ASSERT_THAT((c1.m_sumArr+c2.m_sumArr+c3.m_sumArr) == 1000);
	
END_UNIT

UNIT(multiple_consumers_multiple_producers)

	WaitableQueue<Cat> q;
	Consumer c1(q, 2500, 10000);
	Consumer c2(q, 500, 10000);
	Consumer c3(q, 1250, 10000);
	Consumer c4(q, 250, 10000);
	Consumer c5(q, 500, 10000);
	Consumer c6(q, 750, 10000);
	Consumer c7(q, 250, 10000);
	Consumer c8(q, 260, 10000);
	Consumer c9(q, 240, 10000);
	Consumer c10(q, 300, 10000);
	Consumer c11(q, 200, 10000);
	Consumer c12(q, 2300, 10000);
	Consumer c13(q, 700, 10000);
	
	Producer p1(q, 0, 1500, 0);
	Producer p2(q, 1500, 2700, 1);
	Producer p3(q, 2700, 3650, 2);
	Producer p4(q, 3650, 4250, 3);
	Producer p5(q, 4250, 6120, 4);
	Producer p6(q, 6120, 7698, 5);
	Producer p7(q, 7698, 8362, 6);
	Producer p8(q, 8362, 9240, 7);
	Producer p9(q, 9240, 9500, 8);
	Producer p10(q, 9500, 9762, 9);
	Producer p11(q, 9762, 10000, 10);
	

	Thread t1(c1);
	Thread t2(c2);
	Thread t3(c3);
	Thread t4(c4);
	Thread t5(c5);
	Thread t6(c6);
	Thread t7(c7);
	Thread t8(c8);
	Thread t9(c9);
	Thread t10(c10);
	Thread t11(c11);
	Thread t12(c12);
	Thread t13(c13);
	
	Thread t14(p1);
	Thread t15(p2);
	Thread t16(p3);
	Thread t17(p4);
	Thread t18(p5);
	Thread t19(p6);
	Thread t20(p7);
	Thread t21(p8);
	Thread t22(p9);
	Thread t23(p10);
	Thread t24(p11);
/*
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	t16.join();
	t17.join();
	t18.join();
	t19.join();
	t20.join();
	t21.join();
	t22.join();
	t23.join();
	t24.join(); */

	std::cout<<"the sum is "<<(c1.m_sumArr+c2.m_sumArr+c3.m_sumArr+c4.m_sumArr+c5.m_sumArr+c6.m_sumArr+c7.m_sumArr
	           +c8.m_sumArr+c9.m_sumArr+c10.m_sumArr+c11.m_sumArr+c12.m_sumArr+c13.m_sumArr)<<std::endl;
	ASSERT_THAT( (c1.m_sumArr+c2.m_sumArr+c3.m_sumArr+c4.m_sumArr+c5.m_sumArr+c6.m_sumArr+c7.m_sumArr
	           +c8.m_sumArr+c9.m_sumArr+c10.m_sumArr+c11.m_sumArr+c12.m_sumArr+c13.m_sumArr) == 10000);
	           
    ASSERT_THAT(q.IsEmpty() == true);

	
	
END_UNIT

UNIT(thread_pool_ctor_and_dtor)
	ThreadPool t(4);
	t.GracefulShutdown();
END_UNIT

UNIT(submit_work)
	ThreadPool t(7);
	
	const int size = 5;
	Dog** dogs = new Dog*[size];	
	for(int i = 1 ; i <= size ; ++i)
	{
		Dog* p = new Dog(i);
		t.SubmitWork(p);
		dogs[i] = p;
	}
	
	t.GracefulShutdown();
	
	for(int i = 1 ; i <= size ; ++i)
	{
		std::cout << dogs[i]->m_result << std::endl;
		ASSERT_THAT(dogs[i]->m_result == i*i);
	}
	
END_UNIT

UNIT(grow)
	ThreadPool t(900);
	
	const int size = 4000;
	Dog** dogs = new Dog*[size];	
	for(int i = 1 ; i <= size ; ++i)
	{
		Dog* p = new Dog(i);
		t.SubmitWork(p);
		dogs[i] = p;
	}
	
	t.Grow(55);
	
	ASSERT_THAT(t.GetVectorSize() == 955);
	t.GracefulShutdown();
	
END_UNIT

UNIT(shrink)
	ThreadPool t(8);
	
	const int size = 5600;
	Dog** dogs = new Dog*[size];	
	for(int i = 0 ; i < size ; ++i)
	{
		Dog* p = new Dog(i+1);
		t.SubmitWork(p);
		dogs[i] = p;
	}
	
	
	t.Shrink(1);
	
	//std::cout << t.GetVectorSize() << std::endl;
	//ASSERT_THAT(t.GetVectorSize() >= 2 );
	while(t.GetVectorSize() > 7)
		;
	ASSERT_THAT(t.GetVectorSize() == 7 );

	std::cout << "Going to shutdown" <<std::endl;

	t.GracefulShutdown();
	
	sleep(1);
	
	ASSERT_THAT(t.GetVectorSize() == 0 );
	
	
	
END_UNIT

TEST_SUITE(Queue_test)

	TEST(push)
	TEST(check_if_fifo)
	TEST(multiple_consumers_one_producers)
	TEST(multiple_consumers_multiple_producers)
	TEST(thread_pool_ctor_and_dtor)
	TEST(submit_work)
	TEST(grow)
	TEST(shrink)

END_SUITE
