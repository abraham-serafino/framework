#include "c4.h"

Array allocateArray (
    uint itemSize,
    uint capacity,
    ptr values,
    uint length
) {
    var result = (Array) {};
    result.items = allocate((capacity + 1) * itemSize);

    if (result.items == NULL) {
        throwException("Unable to reserve memory for array.");
        return result;
    }

    result.itemSize = itemSize;
    result.capacity = capacity;
    result.length = length;

    if (values != NULL && length > 0) {
        memcpy(result.items, values, length * itemSize);
    }

    // set result.items[length] to 'null'
    var base = (byte*) result.items + (length * itemSize);
    memset(base, 0, itemSize);

    return result;
}

ptr arrayItemAt (uint itemSize, Array this, uint index) {
    if (itemSize != this.itemSize) {
        throwException("Incorrect type.");
        return NULL;
    }

    if (this.items == NULL) {
        throwException("Null reference detected.");
        return NULL;
    }

    if (index > this.length) {
        throwException("Array index out of bounds.");
        return NULL;
    }

    return (ptr) ((byte*) this.items + (index * itemSize));
}

boolean shiftArrayRight (
    uint size,
    Array* this,
    uint startIndex,
    uint items
) {
    if (this == NULL) {
        throwException("Null reference detected.");
        return false;
    }

    if ((*this).items == NULL && index > 0) {
        throwException("Null reference detected.");
        return false;
    }

    var itemSize = (*this).itemSize;

    if (itemSize != (*this).itemSize) {
        throwException("Incorrect type.");
        return false;
    }

    if (startIndex > (*this).length) {
        throwException("Array index out of bounds.");
        return false;
    }

    var newLength = (*this).length + items;

    if (newLength > (*this).capacity) {
        var newCapacity = ((*this).capacity || items) * 2;

        if ((*this).items == NULL) {
            (*this).items = allocate(newCapacity * itemSize);
        } else {
            (*this).items = reallocate((*this).items, newCapacity * itemSize);
        }

        if ((*this).items == NULL) {
            // realloc failed
            throwException("Unable to increase the size of an array.");
            return false;
        }

        (*this).capacity = newCapacity;
    }

    var base = (byte*) (*this).items;
    var end = startIndex + items;

    forEach (i, from(newLength),
                downTo(end)
    ) {
        var source = (ptr) (base + ((i - items) * itemSize));
        var dest = (ptr) (base + (i * itemSize));

        memcpy(dest, source, itemSize);
    }

    (*this).length = (*this).length + items;
    return true;
}

Pointer insertArrayItems (
    Array* this, 
    uint index, 
    uint numberOfItems, 
    Pointer value
) {
    var nullPointer = (Pointer) { .data = NULL };

    if (isNull(value)) {
        throwException("Null reference detected.");
        return nullPointer;
    }

    var itemSize = value.size;

    unless (shiftArrayRight(itemSize, this, index, numberOfItems)) {
        return nullPointer;
    }

    var base = (byte*) (*this).items;
    var newItem = (ptr) (base + (index * itemSize));
    memcpy(newItem, value.data, itemSize * numberOfItems);

    return _pointerTo(itemSize, newItem);
}

boolean shiftArrayLeft (
    uint size,
    Array* this,
    uint startIndex,
    uint items
) {
    if (this == NULL) {
        throwException("Null reference detected.");
        return false;
    }

    if ((*this).items == NULL && index > 0) {
        throwException("Null reference detected.");
        return false;
    }

    var itemSize = (*this).itemSize;

    if (itemSize != (*this).itemSize) {
        throwException("Incorrect type.");
        return false;
    }

    if (startIndex >= (*this).length) {
        throwException("Array index out of bounds.");
        return false;
    }

    var base = (byte*) (*this).items;
    var end = startIndex + items;

    forEach (i, from(startIndex),
                upTo(end)
    ) {
        var source = (ptr) (base + (i + items) * itemSize);
        var dest = (ptr) (base + (i * itemSize));

        memcpy(dest, source, itemSize);
    }

    (*this).length = (*this).length - items;
    return true;
}

Pointer _removeArrayItems (
    uint itemSize, 
    Array* this, 
    uint index, 
    uint numberOfItems
) {
    var nullPointer = (Pointer) { .data = NULL };
    var base = (byte*) (*this).items;
    var item = (ptr) (base + (index * itemSize));

    var result = _new (itemSize);
    memcpy(result.data, item, itemSize);

    unless (shiftArrayLeft(itemSize, this, index, numberOfItems)) {
        delete(&result);
        return nullPointer;

    } else {
        return result;
    }
}

