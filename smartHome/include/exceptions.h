#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include "FancyException.h"
#include <sstream>
#include <string.h>
#include <string>
#include <iostream>


class MutexException : public FancyException 
{
public:
    MutexException(const std::string& _msg, const char* _file, size_t _line);
    virtual ~MutexException() throw();
};

class SemaphoreException : public FancyException 
{
public:
    SemaphoreException(const std::string& _msg, const char* _file, size_t _line);
    virtual ~SemaphoreException() throw();

};

class ThreadException : public FancyException 
{
public:
    ThreadException(const std::string& _msg, const char* _file, size_t _line);
    virtual ~ThreadException() throw();

};

/**********************inlines**********************/ 

inline MutexException::MutexException(const std::string& _msg, const char* _file, size_t _line)
: FancyException(_file, _line, _msg){}

inline MutexException::~MutexException() throw(){}


inline SemaphoreException::SemaphoreException(const std::string& _msg, const char* _file, size_t _line)
: FancyException(_file, _line, _msg){}

inline SemaphoreException::~SemaphoreException() throw(){}

inline ThreadException::ThreadException(const std::string& _msg, const char* _file, size_t _line)
: FancyException(_file, _line, _msg){}

inline ThreadException::~ThreadException() throw(){}

#endif 
