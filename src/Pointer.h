#ifndef _C4_POINTER_H
#define _C4_POINTER_H_

#include "gc.h"
#include "c4.h"

typedef ptr (*Allocator)(uint size);
typedef ptr (*Reallocator)(ptr original, uint size);

extern Allocator allocate;
extern Reallocator reallocate;

object (Pointer) {
    uint size;
    ptr data;
};

Pointer _pointerTo (uint size, ptr data);
Pointer _new (uint size);
boolean delete (Pointer* this);
ptr _unbox (uint size, Pointer this);
ptr defaultAllocator (uint size);
ptr defaultReallocator (ptr original, uint size);
void setAllocator (Allocator newAllocator);
void setReallocator (Reallocator newReallocator);

#define pointerTo(T, data) _pointerTo(sizeof(T), data)
#define new(T) _new(sizeof(T))
#define unbox(T, this) (* (T*) _unbox(sizeof(T), this))
#define isNull(this) (this.data == NULL)

#endif // _C4_POINTER_H_
