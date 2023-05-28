

#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <exception>


//operation exceptions !!!

class WrongStackSize : public  std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "WrongStackSize !";
    }
};

class StackUnderflow : public  std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "StackUnderflow !";
    }
};

class StackOverflow : public  std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Wrong StackSize !";
    }
};


#endif // !MYEXCEPIONS_H
