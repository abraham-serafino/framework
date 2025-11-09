#include "c4.h"

int64 calculateBytes(uint count, uint itemSize) {
    var totalBytes = (uint64) count * itemSize;
    
    if (totalBytes > UINT32_MAX) {
        throwException("Array size in bytes exceeds the 32-bit limit.");
        return -1;
    }

    return (uint) totalBytes;
}

Array allocateArray (
    uint itemSize,
    uint capacity,
    ptr values,
    uint length
) {
    var result = (Array) {};

    var totalBytes = (uint) calculateBytes(capacity + 1, itemSize);

    if (totalBytes < 0) {
        return result;
    }

    result.items = allocate(totalBytes);

    if (result.items == NULL) {
        throwException("Unable to reserve memory for array.");
        return result;
    }

    result.itemSize = itemSize;
    result.capacity = capacity;
    result.length = length;

    totalBytes = calculateBytes(length, itemSize);

    if (totalBytes < 0) {
        return result;
    }

    if (values != NULL && length > 0) {
        memcpy(result.items, values, totalBytes);
    }

    // set result.items[length] to 'null'
    var base = (byte*) result.items + totalBytes;
    memset(base, 0, itemSize);

    return result;
}

ptr _arrayItemAt (Array this, uint index, uint itemSize) {
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
    uint itemSize,
    Array* this,
    uint startIndex,
    uint itemCount
) {
    if (this == NULL) {
        throwException("Null reference detected.");
        return false;
    }

    if ((*this).items == NULL && index > 0) {
        throwException("Null reference detected.");
        return false;
    }

    if (itemSize != (*this).itemSize) {
        throwException("Incorrect type.");
        return false;
    }

    if (startIndex > (*this).length) {
        throwException("Array index out of bounds.");
        return false;
    }

    var newLength = (*this).length + itemCount;
    var oldItems = (*this).items;

    var totalBytes = (uint) 0;
    var newCapacity = (*this).capacity || 1;

    while (newLength > newCapacity) {
        newCapacity = 2 * newCapacity;
    }

    if (newCapacity > (*this).capacity) {
        totalBytes = calculateBytes(newCapacity + 1, itemSize);

        if (totalBytes < 0) {
            return false;
        }

        (*this).items = reallocate((*this).items, totalBytes);

        if ((*this).items == NULL) {
            // realloc failed
            throwException(
                "Unable to reserve space to increase array size."
            );

            return false;
        }

        (*this).capacity = newCapacity;
    }

    var base = (*this).items;
    var moveToIndex = itemSize * (startIndex + itemCount);
    var moveTo = base + moveToIndex;

    var moveFromIndex = itemSize * startIndex;
    var moveFrom = base + moveFromIndex;

    totalBytes = itemSize * ((*this).length - startIndex);
    memmove(moveTo, moveFrom, totalBytes);

    (*this).length = newLength;

    var sentinelOffset = calculateBytes(newLength, itemSize);

    if (sentinelOffset < 0) {
        return false;
    } else {
        var sentinelBase = base + sentinelOffset;
        memset(sentinelBase, 0, itemSize);
    }

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

    var $base = (byte*) (*this).items;
    var byteOffset = calculateBytes(index, itemSize);
    var totalBytes = calculateBytes(numberOfItems, itemSize);

    if (byteOffset < 0 || totalBytes < 0) {
        return nullPointer;
    }

    var $newItem = $base + byteOffset;
    memcpy($newItem, value.data, totalBytes);

    return _pointerTo(itemSize, $newItem);
}

boolean shiftArrayLeft (
    uint itemSize,
    Array* this,
    uint startIndex,
    uint itemCount
) {
    if (this == NULL) {
        throwException("Null reference detected.");
        return false;
    }

    if ((*this).items == NULL && startIndex > 0) {
        throwException("Null reference detected.");
        return false;
    }

    if (itemSize != (*this).itemSize) {
        throwException("Incorrect type.");
        return false;
    }

    if (startIndex >= (*this).length) {
        throwException("Array index out of bounds.");
        return false;
    }


    var base = (*this).items;
    var moveToIndex = itemSize * (startIndex - itemCount);
    var moveTo = base + moveToIndex;

    var moveFromIndex = itemSize * startIndex;
    var moveFrom = base + moveFromIndex;

    var totalBytes = itemSize * ((*this).length - startIndex);
    memmove(moveTo, moveFrom, totalBytes);

    var newLength = (*this).length - itemCount;
    (*this).length = newLength;

    if (newLength > 0) {
        var sentinelOffset = calculateBytes(newLength, itemSize);

        if (sentinelOffset < 0) {
            return false; 
        }

        var sentinelBase = (byte*) base + sentinelOffset;
        memset(sentinelBase, 0, itemSize);
    }

    return true;
}

Pointer _removeArrayItems (
    Array* this,
    uint index,
    uint numberOfItems,
    uint itemSize
) {
    var nullPointer = (Pointer) { .data = NULL };
    var base = (byte*) (*this).items;
    var byteOffset = calculateBytes(index, itemSize);

    if (byteOffset < 0) {
        return nullPointer;
    }

    var item = (ptr) (base + byteOffset);
    var result = _new (itemSize);
    memcpy(result.data, item, itemSize);

    unless (shiftArrayLeft(itemSize, this, index, numberOfItems)) {
        delete(&result);
        return nullPointer;

    } else {
        return result;
    }
}

void deleteArray (Array* this) {
    if (this != NULL) {
        if ((*this).items != NULL) {
            free((*this).items);
            (*this).items = NULL;
        }

        (*this).capacity = 0;
        (*this).length = 0;
    }
}
