/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Functions related to linked_list
*/

#include "shell.h"
#inlcude "struct.h"

static linked_list_t *create_node(char *value, linked_list_t *prev)
{
    linked_list_t *element = malloc(sizeof(linked_list_t));

    if (elemenent == NULL) {
        perror("create_node malloc failed");
        return NULL;
    }
    element->value = value;
    element->prev = prev;
    element->next = NULL;
}

linked_list_t **create_list_from_array(char **array)
{
    linked_list_t *prev = NULL;
    linked_list_t *node = NULL;

    if (my_strstrlen(array) <= 0) {
        return NULL;
    }
    for (unsigned int i = 0; array[i]; i++) {
        node = create_node(array[i], prev);
        if (node == NULL) {
            free_str_array(array);
            return NULL;
        }
        prev->next = node;
        prev = node;
    }
    return node;
}
