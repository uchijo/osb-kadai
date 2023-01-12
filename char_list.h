// linked list struct named char_list_elem
typedef struct char_list_elem {
    char *data;
    struct char_list_elem *next;
} char_list_elem;

// linked list struct
typedef struct char_list {
    char_list_elem *head;
} char_list;

char *get_string(char_list *list, int n);
int length(char_list *list);
void append_to_list(char_list *list, char *data);
void print_list(char_list *list);
void free_list(char_list *list);
void insert_elem(char_list *list, int n, char *data);
void remove_elem(char_list *list, int n);
void modify_elem(char_list *list, int n, char *data);
char_list *read_file(char *path);
char_list_elem *create_elem(char *data);
char_list_elem *copy_elem(char_list_elem *elem);
int index_of(char_list *list, char *data);
char_list *sublist(char_list *list, int n, int m);
char_list *split_string(char *string, char *delimiter);
