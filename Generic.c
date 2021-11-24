#define cbrt(X) _Generic((X), long double: cbrtl, \
                              float: cbrtf,       \
                              default: cbrt       \
                        )(X)
