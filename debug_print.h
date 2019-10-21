#ifndef _H_DEBUG_PRINT
#define _H_DEBUG_PRINT


#ifdef DEBUG
    #include <stdio.h>
    #define DEBUG_PRINT(fmt, ...) printf("DEBUG " __FILE__ ": " fmt, ##__VA_ARGS__)
#else  //DEBUG
    #define DEBUG_PRINT(fmt, ...)
#endif //DEBUG


#endif //_H_DEBUG_PRINT
