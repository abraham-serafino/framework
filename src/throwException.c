#include "throwException.h"

ExceptionHandler exceptionHandler = defaultExceptionHandler;

void defaultExceptionHandler (cstring message) {
    fprintf(stderr, "\n%s\n", message);
    exit(1);
}

void throwException (cstring message) {
    if (message != NULL && exceptionHandler != NULL) {
        exceptionHandler(message);
    }
}

void setExceptionHandler (ExceptionHandler newHandler) {
    exceptionHandler = newHandler;
}
