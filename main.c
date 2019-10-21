#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debug_print.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include "utils.h"

void print_usage(char * prog_name) {
    printf("Usage: %s key rotor_order swaps enc/dec_text\n", prog_name);
    printf("\n\tkey          - 3 characters\n");
    printf("\n\trotor_order  - 3 characters\n");
    printf("\n\tswaps        - TODO EXPLAIN\n");
    printf("\n\tenc/dec_text - the text to encode or decode\n");
}

int run_alg(char *out_text, char *key, char *rotors, char *swaps, char *text) {
    size_t out_posn = 0;

    Rotor l_rotor = {0}, m_rotor = {0}, r_rotor = {0};
    if( ! build_rotor(&r_rotor, rotors[2], to_upper(key[2]), 0,        &m_rotor) ||
        ! build_rotor(&m_rotor, rotors[1], to_upper(key[1]), &r_rotor, &l_rotor) ||
        ! build_rotor(&l_rotor, rotors[0], to_upper(key[0]), &m_rotor, 0) )
    {
        return 1;
    }

    Plugboard plugs = {0};
    if( ! build_plugboard(&plugs, swaps) ) {
        return 2;
    }

    for( size_t ind = 0; ind < strlen(text); ind += 1 ) {
        DEBUG_PRINT("\nSending Letter Into Machine\n");
        DEBUG_PRINT("Input: %c\n", text[ind]);
        if( text[ind] == ' ' ) {
            // Ignore spaces
            continue;
        } else if( !is_letter(text[ind]) ) {
            // Fail on invalid characters
            return 3;
        }

        char plug_result = plugboard_swap(&plugs, to_upper(text[ind]));
        DEBUG_PRINT("Plugboard result: %c\n", plug_result);
        step_rotor(&l_rotor);
        char left_pass = encode_letter(&l_rotor, plug_result, ENC_FORW);
        DEBUG_PRINT("Left to right rotor pass: %c\n", left_pass);
        char refl_output = reflect(left_pass);
        DEBUG_PRINT("Reflector output: %c\n", refl_output);
        char final_letter = encode_letter(&r_rotor, refl_output, ENC_BACK);
        DEBUG_PRINT("Right to left rotor pass: %c\n", final_letter);
        out_text[out_posn] = plugboard_swap(&plugs, final_letter);
        DEBUG_PRINT("Output: %c\n\n", out_text[out_posn]);
        out_posn += 1;
    }

    out_text[out_posn] = 0;

    return 0;
}

int main(int argc, char * argv[]) {
    if( argc != 5 ) {
        print_usage(argv[0]);
        return 1;
    }
    
    char * key = argv[1], * rotors = argv[2], * swaps = argv[3],
            * text = argv[4];

    char * out_text = calloc(strlen(text) + 1, 1);
    if( out_text == 0 ) {
        fprintf(stderr, "Error allocating memory.\n");
        return 2;
    }

    if( strlen(key) != 3 || strlen(rotors) != 3 || (strlen(swaps) % 2 != 0) ) {
        fprintf(stderr, "Invalid key, rotor, or swap length\n");
        print_usage(argv[0]);
        return 1;
    }

    int run_ret = run_alg(out_text, key, rotors, swaps, text);
    if( run_ret == 1 ) {
        fprintf(stderr, "Invalid rotor index\n");
        print_usage(argv[0]);
        return 1;
    } else if( run_ret == 2 ) {
        fprintf(stderr, "Invalid swaps\n");
        print_usage(argv[0]);
        return 1;
    } else if( run_ret == 3 ) {
        fprintf(stderr, "Invalid characters for encode\n");
        return 2;
    }

    printf("%s\n", out_text);

    return 0;
}
