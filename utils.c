#include "utils.h"

int is_letter(char val) {
    return (val >= 'A' && val <= 'Z') || (val >= 'a' && val <= 'z');
}

char to_upper(char val) {
    return val > 'Z' ? val - 'a' + 'A' : val;
}

char * strncpy(char *dest, const char *src, size_t n){
    size_t ind = 0;
    for(ind = 0; (ind < n) && (src[ind] != 0); ind += 1) {
        dest[ind] = src[ind];
    }
    // Copy the null if we can
    if(ind < n) {
        dest[ind] = src[ind];
    }
    return dest;
}

size_t strlen(const char *s) {
    size_t ind = 0;
    for(ind = 0; s[ind] != 0; ind += 1) {
    }
    return ind;
}
