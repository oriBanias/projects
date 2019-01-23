#ifndef __FANCYEXCEPTION_H__
#define __FANCYEXCEPTION_H__

#include <exception> 
#include <string>
#include <sstream>
#include <string.h>

class FancyException : public std::runtime_error 
{
public:
	FancyException(const char* _file, size_t _line, const std::string& _msg);
	virtual ~FancyException() throw();
		
	private:
		std::string MakeStr(const char* _file, size_t _line, const std::string& _msg);
	private:
		std::string m_msg;
};  

inline FancyException::FancyException(const char* _file, size_t _line, const std::string& _msg) 
: std::runtime_error( MakeStr(_file, _line, _msg) ){}

inline FancyException::~FancyException() throw(){}

inline std::string FancyException::MakeStr(const char* _file, size_t _line, const std::string& _msg)
{
	std::stringstream ss;

    ss << _line ;

	m_msg = std::string(_file) + std::string(": ") + ss.str() + std::string(": ") + _msg + std::string("\n");
	
	return m_msg;
} 


#endif
