#include "Exception.h"

MathException::MathException(const char *message)
    : _message(message) { }

NotFoundValueException::NotFoundValueException(const char *message)
    : MathException(message) { }

const char* NotFoundValueException::what() const noexcept
{
    return _message;
}
