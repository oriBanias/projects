#ifndef __Ustring_H__
#define __Ustring_H__
#include <iostream>
#include <stddef.h>
#include <cwchar>

template<typename T>
class Ustring
{
public:
    explicit Ustring(const T* _str = 0);
    Ustring(const Ustring& _str); 
    ~Ustring();
    
    Ustring& operator=(const Ustring& _other);  
    Ustring& operator=(const T* _other);
    Ustring& operator+=(const Ustring& _other);
    Ustring& operator+=(const T* _other);
    const T operator[](int i) const;
	T& operator[](int i);
    
    size_t length() const;

    void setString(const T* _str);

    const T* getString() const;

    void touppercase();

    void tolowercase();

    int compare(const T* _str) const; 
    
    static size_t GetCapacity();
    
    static size_t SetCapacity(size_t _capacity);
  
	
private:
	static const size_t cm_allocConst = 64;
   	T* m_str;
    size_t m_length;
   	static size_t sm_objectCounter;
	static size_t sm_capacity;  
	size_t power2(size_t _num) const;   	 
};

template<typename T>
class StringTrait
{
public:
	
	static const T* sm_empty();
	static size_t len(const T* _str); 
	static T* cat(T* _str1, const T* _str2);    
    static void cpy(T* _str1, const T* _str2);
    static int cmp(const T* _str1, const T* _str2);
    static T* Begin(T* _str);
    static T* End(T* _str);
    static void Print( std::basic_ostream<T>& _out, Ustring<T>& _str);  
};

template<typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& _out, Ustring<T>& _str)
{
	StringTrait<T>::Print(_out, _str);
	return _out;
}

template<typename T>
inline const T* Ustring<T>::getString() const
{
	return m_str; 
}

template<typename T>
size_t Ustring<T>::length() const
{
	return m_length;
}

template<typename T>
inline bool operator<(const Ustring<T>& _left, const Ustring<T>& _right)
{
	return  (_left.compare(_right.getString()) < 0);
}

template<typename T>
inline bool operator!=(const Ustring<T>& _left, const Ustring<T>& _right)
{
	return  !(_left == _right);
}

template<typename T>
inline bool operator==(const Ustring<T>& _left, const Ustring<T>& _right)
{
	return  _left.compare(_right.getString()) == 0;
}

template<typename T>
const T Ustring<T>::operator[](int i) const
{
	return m_str[i];
}

template<typename T>
T& Ustring<T>::operator[](int i)
{
	return m_str[i];
}

template<typename T>
Ustring<T> operator+(const Ustring<T>& first, const T* second) 
{	
	Ustring<T> c(first);
	return(c += second);
}

template<typename T>
Ustring<T> operator+(const T* first, const Ustring<T>& second) 
{	
	Ustring<T> c(second);
	return(c += first);
}

template<typename T>
Ustring<T> operator+(const Ustring<T>& first, const Ustring<T>& second) 
{	

	Ustring<T> c(first);
	return (c+=second);
}

#include "Ustring.hpp"
#endif
