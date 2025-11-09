#include "c4.h"
#include "Person.h"

int main () {
    GC_INIT();

    var ary = newArray(int, 1, 2, 3);
    debug("%d\n", arrayItemAt(ary, int, 0));

    var employees = arrayOf(Person, 1);
    var $bob = newPerson("Bob", 21);
    insertArrayItem(employees, 0, $bob);

    var $alice = insertArrayItem(employees, 0, newPerson("Alice", 50));

    while (employees.length > 0) {
        var $person = removeArrayItem(employees, 0, Person);
        printPerson($person);
    }

    var str = newArray(byte, "H world");
    puts((byte*) str.items);

    insertArrayItems(&str, 1, 4, pointerTo(byte, "ello"));
    puts((byte*) str.items);

    removeArrayItems(str, 5, 6, char);

    insertArrayItem(str, 5, pointerTo(byte, "!"));
    puts((byte*) str.items);

    var nums = newArray(int, 1, 5);
    var newNums = (int[]) { 2, 3, 4 };

    insertArrayItems(&nums, 1, 3, pointerTo(int, newNums));

    while (nums.length > 0) {
        var $num = dequeueArrayItem(nums, int);
        debug("%d\n", unbox(int, $num));
    }

    debug("\n");

    var staque = arrayOf(int, 0);

    forEach (i, from(10), downTo(1)) {
        pushArrayItem(staque, pointerTo(int, &i));
    }

    while (staque.length > 0) {
        var $item = popArrayItem(staque, int);
        var result = unbox(int, $item);

        debug( "%d\n", result);
    }

    return 0;
}
