#include "Person.h"

void printPerson (Pointer pThis) {
    unless (isNull(pThis)) {
        var this = unbox(Person, pThis);
        printf("%s is %d years old.\n", this.name, this.age);
    }
}

Pointer newPerson (cstring name, int age) {
    var this = new (Person);

    unbox(Person, this).name = name;
    unbox(Person, this).age = age;

    return this;
}
