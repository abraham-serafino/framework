#ifndef _C4_THROW_EXCEPTION_H_
#define _C4_THROW_EXCEPTION_H_

#include "c4.h"

typedef void (*ExceptionHandler)(cstring message);
extern ExceptionHandler exceptionHandler;

void throwException (cstring message);
void defaultExceptionHandler (cstring message);
void setExceptionHandler (ExceptionHandler newHandler);

#endif // _C4_THROW_EXCEPTION_H_
