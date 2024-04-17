/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell2-nicolas.nunney
** File description:
** my_str_array_dup_ban_str.c
*/

#include <stdlib.h>
#include "my.h"

static int my_strstrlen_ban_str(char **array, char *str)
{
    int cpt = 0;

    for (int i = 0; my_strcmp(array[i], str) != 0 && array[i]; i++) {
        cpt++;
    }
    return cpt;
}

char **my_str_array_dup_ban_str(char **array, char *str)
{
    char **new_array;
    int i = 0;
    bool found = false;

    for (int i = 0; array[i]; i++) {
        if (my_strcmp(array[i], str) == 0) {
            found = true;
            break;
        }
    }
    if (!found)
        return array;
    new_array = malloc(sizeof(char *) *
        my_strstrlen_ban_str(array, str) + 2);
    while (my_strcmp(array[i], str) != 0 && array[i]) {
        new_array[i] = my_strdup(array[i]);
        i++;
    }
    new_array[i] = NULL;
    return new_array;
}
