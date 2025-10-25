#ifndef _C4_H_
#define _C4_H_

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"
#include "throwException.h"
#include "Pointer.h"
#include "Array.h"

#ifndef _C4_NO_DEBUG_
    #define debug printf
#else
    #define debug
#endif //_C4_NO_DEBUG_


#define from(x) x

#define forEach(i, x, ...) for (int i = x; i __VA_ARGS__ i)
#define upTo(x) < (x); ++
#define downTo(x) >= (x); --

// forEach (i, from(1), upTo(10)) { ... }
// forEach (i, from(25), downTo(20)) { ... }

#define loop_until(...) while(! (__VA_ARGS__))
#define unless(...) if(! (__VA_ARGS__))

#endif // _C4_H_

