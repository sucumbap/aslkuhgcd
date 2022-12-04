#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static bool __result;
static char * __funcname;


#define FAIL "\033[1;31mFAIL!(%d)\033[0m"
#define OK "\033[1;32mOK!\033[0m\n"

#define ERROR_ASSERTION(e) \
    printf("%s: ", __funcname); \
    printf(FAIL, __LINE__); \
    printf(": assertion '%s' failed!\n", e); \
    __result = false

#define ERROR(msg, p1, p2) \
    printf("%s: ", __funcname); \
    printf(FAIL, __LINE__); \
    printf(msg, p1, p2); \
    __result = false

#define ERROR_INT(i1, i2) \
    ERROR(": expected %d, actual %d\n", (i1), (i2))

#define ERROR_STR(s1, s2) \
    ERROR(": expected %s, actual %s\n", s1, s2)
   

#define ASSERT_EQUAL_INT(i1, i2) \
    do  { \
        int _i1 = (i1), _i2 = (i2); \
        if (_i1 != _i2) { \
            ERROR_INT(_i1, _i2); \
            return; \
        } \
    } \
    while(0)

#define ASSERT_EQUAL_STR(s1, s2) \
    do  { \
        char *_s1=(s1), *_s2=(s2); \
        if (strcmp(_s1, _s2) != 0) { \
            ERROR_STR(_s1, _s2); \
            return; \
        } \
    } \
    while(0)
    

#define ASSERT_TRUE(e) \
    do { \
        if (!(e)) { \
            ERROR_ASSERTION(#e); \
            return; \
        } \
    }\
    while(0)


#define ASSERT_FALSE(e)  ASSERT_TRUE(!(e))
    
        
#define TEST(f)  \
    do { \
        __result = true; \
        __funcname = #f; \
        f(); \
        if (__result) printf("%s: %s", __funcname, OK); \
    } while(0)
