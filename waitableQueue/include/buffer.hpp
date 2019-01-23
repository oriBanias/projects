#include "Buffer.h"
#include <cwchar>
#include <iterator>
#include <string>
#include <algorithm>
#include <cwchar>

template <typename T>
Buffer<T>::Buffer(const Ustring& _str)
{
	if ((_str.m_buff != NULL) && (_str.m_length > 0))
	{
		m_length = _str.length();
		sm_capacity = power2(m_length+1);
		m_buff = new T[sm_capacity];
    	setString(_str.getString());
    }
    ++sm_objectCounter;
}

template <typename T>
Ustring<T>::~Ustring()
{
    delete []m_buff;
    --sm_objectCounter;
}

template <typename T>
Ustring<T>& Ustring<T>::operator=(const Ustring& _other)
{
	if (this == &_other)
	{
		return *this;
	}
	
	T* p = new T[_other.m_length];
	StringTrait<T>::cpy(p, _other.m_buff);

	delete[] m_buff;
	
	m_buff = p;
	m_length = _other.m_length;

	return *this;
}
