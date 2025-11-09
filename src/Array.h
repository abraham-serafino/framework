// @TODO 
//
// 1. rewrite pop and dequeue as functions that check
//      this.length
//
// 2. move type specifier to last argument position
//

#ifndef _C4_ARRAY_H_
#define _C4_ARRAY_H_

#include "c4.h"

object (Array) {
    uint64 itemSize;
    uint64 capacity;
    uint64 length;
    ptr items;
};

Array allocateArray (
    uint itemSize,
    uint capacity,
    ptr values,
    uint length
);

ptr _arrayItemAt (Array this, uint index, uint itemSize);

Pointer insertArrayItems (
    Array* this, 
    uint index, 
    uint numberOfItems, 
    Pointer value
);

Pointer _removeArrayItems (
    Array* this,
    uint index,
    uint numberOfItems,
    uint itemSize
);

void deleteArray(Array* this);

#define queueArrayItem(this, value) \
    insertArrayItem(this, 0, value)

#define dequeueArrayItem(this, T) \
    removeArrayItem(this, (T), 0)

#define pushArrayItem(this, value) \
    insertArrayItem(this, this.length, value)

#define popArrayItem(this, T) \
    removeArrayItem( \
        this, \
        this.length > 0 ? this.length - 1 : 0, \
        (T) \
    )

#define insertArrayItem(this, index, value) \
    insertArrayItems(&this, index, 1, value)

#define removeArrayItems(this, index, numberOfItems, T) \
    _removeArrayItems(&this, index, numberOfItems, (sizeof(T)))

#define removeArrayItem(this, index, T) \
    _removeArrayItems(&this, index, 1, (sizeof(T)))

#define arrayOf(T, capacity) \
    allocateArray((sizeof(T)), capacity, NULL, 0)

#define newArray(T, ...) \
    allocateArray( \
        (sizeof(T)), \
        (sizeof((T[]) {__VA_ARGS__}) / sizeof(T)),\
        (T[]) {__VA_ARGS__ }, \
        (sizeof((T[]) {__VA_ARGS__}) / sizeof(T))\
    )

#define arrayItemAt(this, T, index) \
    (* ((T*) _arrayItemAt(this, index, (sizeof(T)))))

#endif // _C4_ARRAY_H
