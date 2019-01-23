#include "atomicFlag.h"

AtomicFlag::AtomicFlag()
:
m_flag(1)
{
	
}

void AtomicFlag::raise()
{
	if (m_flag < 1)
	{
		__sync_fetch_and_add (&m_flag, 1);
	}
}

void AtomicFlag::down()
{
	__sync_lock_test_and_set (&m_flag, 0);
}

bool AtomicFlag::isUp()
{
	return __sync_fetch_and_add (&m_flag, 0) == 1;
}
