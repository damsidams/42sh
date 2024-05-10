/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Functions related to linked_list
*/

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "shell.h"
#include "struct.h"

static void free_prev(linked_list_t *list)
{
    linked_list_t *prev = NULL;
    linked_list_t *cpy = NULL;

    if (list && list->prev) {
        cpy = list->prev;
    }
    while (cpy) {
        prev = cpy->prev;
        if (cpy->value)
            free(cpy->value);
        free(cpy);
        cpy = prev;
    }
}

void free_list(linked_list_t *list)
{
    linked_list_t *next = NULL;

    free_prev(list);
    while (list) {
        if (list->value)
            free(list->value);
        next = list->next;
        free(list);
        list = next;
    }
}

static linked_list_t *create_node(char *value, linked_list_t *prev)
{
    linked_list_t *element = malloc(sizeof(linked_list_t));

    if (element == NULL) {
        perror("create_node malloc failed");
        return NULL;
    }
    if (strcmp(value, "") == 0) {
        element->value = value;
    } else {
        element->value = find_cmd_in_line(value);
    }
    element->prev = prev;
    element->next = NULL;
    return element;
}

linked_list_t *create_list_from_array(char **array)
{
    linked_list_t *prev = NULL;
    linked_list_t *node = NULL;

    if (my_strstrlen(array) <= 0) {
        free_str_array(array);
        return NULL;
    }
    for (unsigned int i = 0; array[i]; i++) {
        node = create_node(strdup(array[i]), prev);
        if (node == NULL) {
            free_str_array(array);
            return NULL;
        }
        if (prev) {
            prev->next = node;
        }
        prev = node;
    }
    free_str_array(array);
    return node;
}
