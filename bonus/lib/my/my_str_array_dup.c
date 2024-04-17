/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** my_str_array_dup.c
*/

#include <stdlib.h>
#include "my.h"

char **my_str_array_dup(char **array)
{
    char **array_cpy = malloc(sizeof(char *) * (my_strstrlen(array) + 1));

    for (int i = 0; array[i]; i++)
        array_cpy[i] = my_strdup(array[i]);
    array_cpy[my_strstrlen(array)] = NULL;
    return array_cpy;
}
