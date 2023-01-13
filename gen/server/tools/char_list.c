#include "char_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exit_with_error(char *errorMessage, int line, char *file);

// function that gets n element from char_list_elem list
char *get_string(char_list *list, int n) {
    char_list_elem *current = list->head;
    for (int i = 0; i < n; i++) {
        current = current->next;
    }
    return current->data;
}

// function that returns length of char_list_elem list
int length(char_list *list) {
    int length = 0;
    char_list_elem *current = list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

// function that frees char_list_elem list
void free_list(char_list *list) {
    char_list_elem *current = list->head;
    while (current != NULL) {
        char_list_elem *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

// function that inserts char_list_elem to list
void insert_elem(char_list *list, int n, char *data) {
    char_list_elem *new_elem = malloc(sizeof(char_list_elem));
    new_elem->data = malloc(strlen(data) + 1);
    strcpy(new_elem->data, data);
    if (n == 0) {
        new_elem->next = list->head;
        list->head = new_elem;
    } else {
        char_list_elem *current = list->head;
        for (int i = 0; i < n - 1; i++) {
            current = current->next;
        }
        new_elem->next = current->next;
        current->next = new_elem;
    }
}

// function that removes char_list_elem from list
void remove_elem(char_list *list, int n) {
    if (n == 0) {
        char_list_elem *next = list->head->next;
        free(list->head->data);
        free(list->head);
        list->head = next;
    } else {
        char_list_elem *current = list->head;
        for (int i = 0; i < n - 1; i++) {
            current = current->next;
        }
        char_list_elem *next = current->next->next;
        free(current->next->data);
        free(current->next);
        current->next = next;
    }
}

// function that modifies char_list_elem in list
void modify_elem(char_list *list, int n, char *data) {
    char_list_elem *current = list->head;
    for (int i = 0; i < n; i++) {
        current = current->next;
    }
    free(current->data);
    current->data = malloc(strlen(data) + 1);
    strcpy(current->data, data);
}

// function that appends char_list_elem to list
void append_to_list(char_list *list, char *data) {
    char_list_elem *new_elem = malloc(sizeof(char_list_elem));
    new_elem->data = malloc(strlen(data) + 1);
    strcpy(new_elem->data, data);
    new_elem->next = NULL;
    if (list->head == NULL) {
        list->head = new_elem;
    } else {
        char_list_elem *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_elem;
    }
}

// function that prints char_list_elem list
void print_list(char_list *list) {
    char_list_elem *current = list->head;
    while (current != NULL) {
        printf("%s", current->data);
        current = current->next;
    }
}

char_list_elem *create_elem(char *data) {
    char_list_elem *new_elem = malloc(sizeof(char_list_elem));
    new_elem->data = malloc(strlen(data) + 1);
    strcpy(new_elem->data, data);
    new_elem->next = NULL;
    return new_elem;
}

char_list_elem *copy_elem(char_list_elem *elem) {
    char_list_elem *new_elem = malloc(sizeof(char_list_elem));
    new_elem->data = malloc(strlen(elem->data) + 1);
    strcpy(new_elem->data, elem->data);
    new_elem->next = NULL;
    return new_elem;
}

int index_of(char_list *list, char *data) {
    char_list_elem *current = list->head;
    int index = 0;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

// function that returns char_list_elem list with elements from n to m
char_list *sublist(char_list *list, int n, int m) {
    char_list *new_list = malloc(sizeof(char_list));
    new_list->head = NULL;
    char_list_elem *current = list->head;
    for (int i = 0; i < n; i++) {
        current = current->next;
    }
    for (int i = n; i <= m; i++) {
        append_to_list(new_list, current->data);
        current = current->next;
    }
    return new_list;
}

// function that reads file and returns char_list_elem list
char_list *read_file(char *path) {
    FILE * file = fopen(path, "r");
    if (file == NULL) {
        exit_with_error("Error opening file", __LINE__, __FILE__);
    }
    char_list *list = malloc(sizeof(char_list));
    list->head = NULL;
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        append_to_list(list, line);
    }
    free(line);
    fclose(file);
    return list;
}

// function that splits string by delimiter and returns char_list
char_list *split_string(char *string, char *delimiter) {
    char *string_copy = malloc(strlen(string) + 1);
    strcpy(string_copy, string);

    char_list *list = malloc(sizeof(char_list));
    list->head = NULL;

    char *token = strtok(string_copy, delimiter);
    while (token != NULL) {
        append_to_list(list, token);
        token = strtok(NULL, delimiter);
    }
    return list;
}
