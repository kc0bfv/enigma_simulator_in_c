typedef struct __plugboard {
    char board[27];
} Plugboard;

int build_plugboard(Plugboard *plugs, char *swaps);

char plugboard_swap(Plugboard *plugs, char inval);
