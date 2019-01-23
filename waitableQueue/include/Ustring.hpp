#include "Ustring.h"
#include <cwchar>
#include <iterator>
#include <string>
#include <algorithm>
#include <cwchar>

template <typename T>
size_t Ustring<T>::sm_objectCounter = 0;

template <typename T>
size_t Ustring<T>::sm_capacity = cm_allocConst;

template <>
void StringTrait<char>::Print(std::basic_ostream<char>& _out, Ustring<char>& _str)
{
	_out<<_str.getString();
}

template <>
void StringTrait<wchar_t>::Print(std::basic_ostream<wchar_t>& _out, Ustring<wchar_t>& _str)
{
	_out<<_str.getString();
}

template <>
size_t StringTrait<char>::len(const char* _str)
{
	return strlen(_str)+1;
} 

template <>
size_t StringTrait<wchar_t>::len(const wchar_t* _str)
{
	return wcslen(_str)+1;
} 

template <>
char* StringTrait<char>::cat(char* _str1, const char* _str2)
{
	return strcat(_str1, _str2);
}

template <>
wchar_t* StringTrait<wchar_t>::cat(wchar_t* _str1, const wchar_t* _str2)
{
	return wcscat(_str1, _str2);
}

template <>
int StringTrait<char>::cmp(const char* _str1, const char* _str2)
{
	return strcmp(_str1, _str2);
} 

template <>
int StringTrait<wchar_t>::cmp(const wchar_t* _str1, const wchar_t* _str2)
{
	return wcscmp(_str1, _str2);
} 

template <>
void StringTrait<char>::cpy(char* _str1, const char* _str2)
{
	strcpy(_str1, _str2);
} 

template <>
void StringTrait<wchar_t>::cpy(wchar_t* _str1, const wchar_t* _str2)
{
	wcscpy(_str1, _str2);
} 

template <>
const char* StringTrait<char>::sm_empty()
{
	return "";
}

template <>
const wchar_t* StringTrait<wchar_t>::sm_empty()
{
	return L"";
}


template <typename T>
T* StringTrait<T>::Begin(T* _str)
{
	return _str;
}

template <typename T>
T* StringTrait<T>::End(T* _str)
{
	return _str + StringTrait<T>::len(_str);
}

template <typename T>
size_t Ustring<T>::power2(size_t _num) const
{
	size_t mod = _num % cm_allocConst;
	size_t div = _num / cm_allocConst;
	if (mod > 0)
	{
		++div;
	}
	return (div * cm_allocConst);
}

template <typename T>
Ustring<T>::Ustring(const T* _str) 
{
    if (_str == NULL)
    {
    	_str = StringTrait<T>::sm_empty();
	}
	
	m_length = StringTrait<T>::len(_str);
	sm_capacity = power2(m_length+1);
	m_str = new T[sm_capacity];
	StringTrait<T>::cpy(m_str, _str);
	
     ++sm_objectCounter;
}

template <typename T>
Ustring<T>::Ustring(const Ustring& _str)
{
	if ((_str.m_str != NULL) && (_str.m_length > 0))
	{
		m_length = _str.length();
		sm_capacity = power2(m_length+1);
		m_str = new T[sm_capacity];
    	setString(_str.getString());
    }
    ++sm_objectCounter;
}

template <typename T>
Ustring<T>::~Ustring()
{
    delete []m_str;
    --sm_objectCounter;
}


int transformToUpper(int x)
{
	const int dif = 'a' - 'A';
	if ((x >= 'a') && (x <= 'z')) // check if lower case letter
	{
		x= ((x) - dif);
	}
	return x;
}

int transformToLower(int x)
{
	const int dif = 'a' - 'A';
	
	if ((x >= 'A') && (x <= 'Z')) // c	heck if upper case letter
	{
		x = ((x) + dif);
	}
	
	return x;
}

template <typename T>
void Ustring<T>::touppercase()
{
	std::transform(StringTrait<T>::Begin(m_str)	, StringTrait<T>::End(m_str), StringTrait<T>::Begin(m_str), transformToUpper);
}

  

template <typename T>
void Ustring<T>::tolowercase()
{
	std::transform(StringTrait<T>::Begin(m_str)	, StringTrait<T>::End(m_str), StringTrait<T>::Begin(m_str), transformToLower);
}

template <typename T>
Ustring<T>& Ustring<T>::operator=(const Ustring& _other)
{
	if (this == &_other)
	{
		return *this;
	}
	
	T* p = new T[_other.m_length];
	StringTrait<T>::cpy(p, _other.m_str);

	delete[] m_str;
	
	m_str = p;
	m_length = _other.m_length;

	return *this;
}

template <typename T>
Ustring<T>& Ustring<T>::operator=(const T* _other)
{
	if (_other != NULL)
	{
		StringTrait<T>::cpy(m_str, _other);
		m_length = StringTrait<T>::len(_other);
	}
	
	return *this;
}

template <typename T>
Ustring<T>& Ustring<T>::operator+=(const Ustring& _other)
{
    StringTrait<T>::cat(m_str, _other.m_str);
    m_length = StringTrait<T>::len(m_str);   
	return *this;
}

template <typename T>
Ustring<T>& Ustring<T>::operator+=(const T* _other)
{
	if (_other != NULL)
	{
		StringTrait<T>::cat(m_str, _other);   
	}
	
	m_length = StringTrait<T>::len(m_str);
	
	return *this;
}

template <typename T>
void Ustring<T>::setString(const T* _str)
{
	if (_str == NULL)
    {
    	_str = StringTrait<T>::sm_empty();
	}
	
	m_length = StringTrait<T>::len(_str);
	delete []m_str;
	if ((m_length+1) > sm_capacity)
	{	
		sm_capacity = power2(m_length+1);
	}
	m_str = new T[sm_capacity];
	StringTrait<T>::cpy(m_str, _str);
}

template <typename T>
int Ustring<T>::compare(const T* _str) const
{
	int compareRes = 0;
	if (_str == NULL)
	{
		_str = StringTrait<T>::sm_empty();
	}
	
	compareRes = StringTrait<T>::cmp(m_str, _str);
	
	return compareRes;
}


