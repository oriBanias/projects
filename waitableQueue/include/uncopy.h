#ifndef __UNCOPY_H__
#define __UNCOPY_H__

class UnCopyable
{
public:
	UnCopyable(){}
private:
	UnCopyable(const UnCopyable& _Uncpy);
	UnCopyable& operator=(const UnCopyable& _other);
};

#endif
