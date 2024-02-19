typedef enum{
            NUM_T,
            BOOL_T,
            UNK_T,
            ERR_T
        }
type_synth;

typedef struct lcell lcell;

struct lcell{
            lcell *next;
            type_synth type;
            char *id;
        };


typedef struct{
            lcell *head;
        }
lid;
