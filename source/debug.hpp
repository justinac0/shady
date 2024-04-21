#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#define stmt(s) (s)
#define assert_break(s) { if ((s)) {\
    printf("[%s:%d] Assertion Failed... (%s)\n", __FILE__, __LINE__, #s);\
    exit(-1);}}
#define assert_stmt(s) assert_break(s)

#endif // DEBUG_H

