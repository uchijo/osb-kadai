typedef struct {
    char *type;
    char *name;
} arg_t;

typedef struct {
    char *name;
    char *return_type;
    arg_t *args;
    int args_length;
} rpc_t;
