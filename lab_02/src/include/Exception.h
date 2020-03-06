#ifndef __EXCEPTION_H
#define __EXCEPTION_H

#include <exception>

class MathException : public std::exception
{
public:
    MathException(const char *message);
    virtual const char *what() const noexcept = 0;

protected:
    const char *_message;
};

class NotFoundValueException : public MathException
{
public:
    NotFoundValueException(const char *message);
    const char *what() const noexcept override;
};

#endif // __EXCEPTION_H
