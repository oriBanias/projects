#ifndef __ATOMICFLAG_H__
#define __ATOMICFLAG_H__

class AtomicFlag
{
private:
	int m_flag;
 public:
 	AtomicFlag();
 	void raise();
 	void down();
 	bool isUp();
};

#endif
