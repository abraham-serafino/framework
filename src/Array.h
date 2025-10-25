#ifndef _C4_ARRAY_H_
#define _C4_ARRAY_H_

#include "c4.h"

object (Array) {
    byte itemSize;
    uint capacity;
    uint length;
    ptr items;
};

Array allocateArray (
    uint itemSize,
    uint capacity,
    ptr values,
    uint length
);

ptr arrayItemAt (uint itemSize, Array this, uint index);

Pointer insertArrayItems (
    Array* this, 
    uint index, 
    uint numberOfItems, 
    Pointer value
);

Pointer _removeArrayItems (
    uint itemSize, 
    Array* this, 
    uint index, 
    uint numberOfItems
); 

#define insertArrayItem(this, index, value) \
    insertArrayItems(&this, index, 1, value)

#define removeArrayItems(this, T, index, numberOfItems) \
    _removeArrayItems(sizeof(T), &this, index, numberOfItems)

#define removeArrayItem(this, T, index) \
    _removeArrayItems(sizeof(T), &this, index, 1)

#define arrayOf(T, capacity) \
    allocateArray(sizeof(T), capacity, NULL, 0)

#define newArray(T, ...) \
    allocateArray( \
        sizeof(T), \
        sizeof((T[]) {__VA_ARGS__}), \
        (T[]) {__VA_ARGS__ }, \
        (sizeof((T[]) {__VA_ARGS__}) / sizeof(T))\
    )

#define arrayIndex(T, this, index) \
    (* ((T*) arrayItemAt(sizeof(T), this, index)))

#endif // _C4_ARRAY_H

