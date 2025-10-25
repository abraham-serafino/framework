#ifndef _C4_TYPES_H_
#define _C4_TYPES_H_

#define var auto
#define bitfield(i) _BitInt(i)  // requires C23

#define int8 int8_t
#define byte uint8_t
#define boolean _Bool
#define int16 int16_t
#define word uint16_t
#define int int32_t
#define uint uint32_t
#define double double
#define int128 __int128         // requires CLang or GCC
#define uint128 bitfield(128)   // requires C23

#define cstring char*
#define ptr void*

#define object(name) \
    typedef struct name name; \
    struct name

#define option(name) \
    typedef enum name name; \
    typedef enum name UPPERCASE_##name; \
    enum name

#endif // _C4_TYPES_H_

