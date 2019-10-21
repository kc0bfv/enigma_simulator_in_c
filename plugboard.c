#include "plugboard.h"
#include "utils.h"

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0\0\0"

int build_plugboard(Plugboard *plugs, char *swaps) {
    strncpy(plugs->board, ALPHABET, sizeof(plugs->board));

    for(size_t ind = 0; ind < strlen(swaps); ind += 2) {
        if( !is_letter(swaps[ind]) || !is_letter(swaps[ind+1]) ) {
            return 0;
        }
        char let_1 = to_upper(swaps[ind]), let_2 = to_upper(swaps[ind + 1]);
        plugs->board[let_1-'A'] = let_2;
        plugs->board[let_2-'A'] = let_1;
    }

    return 1;
}

char plugboard_swap(Plugboard *plugs, char inval) {
    return plugs->board[inval-'A'];
}
