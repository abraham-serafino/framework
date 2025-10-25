#include "c4.h"
#include "Person.h"

int main () {
    GC_INIT();

    var ary = newArray(int, 1, 2, 3);
    debug("%d\n", arrayIndex(int, ary, 0));

    var employees = arrayOf(Person, 1);
    var $bob = newPerson("Bob", 21);
    insertArrayItem(employees, 0, $bob);

    var $alice = insertArrayItem(employees, 1, newPerson("Alice", 50));
    var employeeLength = employees.length;

    forEach (i, from(0),
                upTo(employeeLength)
    ) {
        Pointer person = removeArrayItem(employees, Person, 0);
        printPerson(person);
    }

    var str = newArray(int, 1, 5);

    insertArrayItems(&str, 1, 3, (Pointer) {
        .size = sizeof(int) * 3,
        .data = & (int[]) { 2, 3, 4 }
    });

    var strLength = str.length;

    forEach (i, from(0),
                upTo(strLength)
    ) {
        Pointer item = removeArrayItem(str, int, 0);
        printf("%d\n", unbox(int, item));
    }

    return 0;
}

