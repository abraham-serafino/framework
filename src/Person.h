#ifndef _C4_TEST_PERSON_H_
#define _C4_TEST_PERSON_H_

#include "c4.h"

/* #define UPPERCASE_Person Person */

object (Person) {
    cstring name;
    int age;
};

void printPerson (Pointer pThis);
Pointer newPerson (cstring name, int age);

#endif // _C4_TEST_PERSON_H_

