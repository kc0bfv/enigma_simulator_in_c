typedef struct __rotor {
    struct __rotor * next_rotor, * prev_rotor;
    unsigned int rotor_ind;
    char notch;
    char window;
} Rotor;

typedef enum __enc_dir { ENC_FORW, ENC_BACK} enc_dir;

int build_rotor(Rotor * rotor, char rotor_ind, char st_val, Rotor * next_rotor, Rotor * prev_rotor);

void step_rotor(Rotor * rotor);

char encode_letter(Rotor * rotor, char to_code, enc_dir direction);
