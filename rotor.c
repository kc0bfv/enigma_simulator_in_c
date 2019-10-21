#include <stddef.h>

#include "debug_print.h"
#include "rotor.h"

const char NOTCHES[4] = "QEVZ";
const char FORW_ROTORS[4][26] = {
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "VZBRGITYUPSDNHLXAWMJQOFECK"
    };
const char BACK_ROTORS[4][26] = {
        "UWYGADFPVZBECKMTHXSLRINQOJ",
        "AJPCZWRLFBDKOTYUQGENHXMIVS",
        "TAGBPCSDQEUFVNZHYIXJWLRKOM",
        "QCYLXWENFTZOSMVJUDKGIARPHB"
    };

int transform_rotor(char rotor_ind) {
    switch(rotor_ind) {
        case '1':
            return 0;
        case '2':
            return 1;
        case '3':
            return 2;
        case '5':
            return 3;
        default:
            return -1;
    }
}

int build_rotor(Rotor * rotor, char rotor_ind, char st_val,
        Rotor * next_rotor, Rotor * prev_rotor)
{
    int act_ind = transform_rotor(rotor_ind);
    if( act_ind < 0 ) {
        return 0;
    }
    rotor->rotor_ind = (unsigned int) act_ind;

    rotor->next_rotor = next_rotor;
    rotor->prev_rotor = prev_rotor;

    rotor->window = st_val;
    rotor->notch = NOTCHES[rotor->rotor_ind];

    return 1;
}

void step_rotor(Rotor * rotor) {
    if( rotor->next_rotor != 0 && rotor->window == rotor->notch ) {
        step_rotor(rotor->next_rotor);
    }
    rotor->window = rotor->window + 1;
    if( rotor->window > 'Z' ) {
        rotor->window = 'A';
    }
}

char encode_letter(Rotor * rotor, char to_code, enc_dir direction) {
    if( rotor == 0 ) {
        // Recursion base
        return to_code;
    }
    size_t cur_offset = rotor->window - 'A';
    size_t char_ind = to_code - 'A';
    const char (*lookup)[4][26] = 
            (direction == ENC_FORW ? &FORW_ROTORS : &BACK_ROTORS);
    char rotor_char = (*lookup)[rotor->rotor_ind][(char_ind + cur_offset) % 26];
    char out_char = ((((rotor_char - 'A') - cur_offset) + 26) % 26) + 'A';
    DEBUG_PRINT("Rotor offset %li input_index %li rotor out %c rotor "
            "out with offset %c\n", cur_offset, char_ind, rotor_char, out_char);
    return encode_letter(
            direction == ENC_FORW ? rotor->next_rotor : rotor->prev_rotor,
            out_char, direction);
}
