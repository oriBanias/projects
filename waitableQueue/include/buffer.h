#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <iostream>
#include <stddef.h>
#include <cwchar>

template <typename T>
class Buffer
{
public:
	Buffer(const T* _buf = 0);
	Buffer(const Buffer& _buf); 
    ~Buffer();
    
    Buffer& operator=(const Buffer& _other);
    
    size_t length() const;

    void setString(const T* _str);

    const T* getString() const;
    
private:
	static const size_t cm_allocConst = 64;
    size_t m_length;
   	static size_t sm_objectCounter;
	static size_t sm_capacity;  
	size_t power2(size_t _num) const;
	T* m_buff;
}

template<typename T>
class StringTrait
{
public:
	
	static const T* sm_empty();
	static size_t len(const T* _str); 
	static T* cat(T* _str1, const T* _str2);    
    static void cpy(T* _str1, const T* _str2);
    static size_t cmp(const T* _str1, const T* _str2);
    static T* Begin(T* _str);
    static T* End(T* _str);
    static void Print( std::basic_ostream<T>& _out, Buffer<T>& _str);  
};

#include "buffer.hpp"
#endif
