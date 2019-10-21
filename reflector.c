#include "reflector.h"

const char REFLECTOR[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

char reflect(char in_val) {
    return REFLECTOR[in_val - 'A'];
}
