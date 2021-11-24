#define cbrt(X) _Generic((X), long double: cbrtl, \
                              float: cbrtf,       \
                              default: cbrt       \
                        )(X)

#include <stdio.h>

#define TYPENAME_CASE(type)                         \
    type: #type,

#define TYPENAME_POINTER_CASE(type)                 \
    TYPENAME_CASE(type)                             \
    TYPENAME_CASE(type *)                           \

#define TYPENAME_UNSIGNED_CASE(type)                \
    TYPENAME_POINTER_CASE(type)                     \
    TYPENAME_POINTER_CASE(unsigned type)            \

#define TYPENAME(x) _Generic((x),                   \
    TYPENAME_POINTER_CASE(_Bool)                    \
    TYPENAME_UNSIGNED_CASE(char)                    \
    TYPENAME_UNSIGNED_CASE(short)                   \
    TYPENAME_UNSIGNED_CASE(long)                    \
    TYPENAME_UNSIGNED_CASE(long long)               \
    TYPENAME_POINTER_CASE(float)                    \
    TYPENAME_POINTER_CASE(double)                   \
    TYPENAME_POINTER_CASE(long double)              \
    TYPENAME_POINTER_CASE(float _Complex)           \
    TYPENAME_POINTER_CASE(double _Complex)          \
    TYPENAME_CASE(void *)                           \
    default: "other"                                \
)

int main(int argc, char * argv[]) {
    double _Complex c;
    double _Complex * p = &c;

    puts(TYPENAME(p));

    return 0;
}
