#include "Pointer.h"

Allocator allocate = &defaultAllocator;
Reallocator reallocate = &defaultReallocator;

Pointer _new (uint size) {
    Pointer this = { .data = allocate(size) };

    if (this.data == NULL) {
        throwException("Unable to reserve memory.");        
        return this;
    }

    this.size = size;

    return this;
}

boolean delete (Pointer* this) {
    if (this != NULL && this->data != NULL) {
        free(this->data);
        this->data = NULL;

        return true;
    }

    return false;
}

ptr _unbox (uint size, Pointer this) {
    if (isNull(this)) {
        throwException("Null reference detected.");
        return NULL;
    }

    if (this.size != size) {
        throwException("Incorrect type detected.");
        return NULL;
    }

    return this.data;
}

Pointer _pointerTo (uint size, ptr data) {
    Pointer this;
    this.data = data;
    this.size = size;

    return this;
}

ptr defaultAllocator (uint size) {
    return GC_MALLOC(size);
}

ptr defaultReallocator (ptr original, uint size) {
    return GC_REALLOC(original, size);
}

void setAllocator (Allocator newAllocator) {
    allocate = newAllocator;
}

void setReallocator (Reallocator newReallocator) {
    reallocate = newReallocator;
}

