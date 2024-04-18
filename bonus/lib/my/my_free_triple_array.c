/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell2-nicolas.nunney
** File description:
** my_free_triple_array.c
*/

#include <stdlib.h>
#include "my.h"

void free_triple_array(char ***array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++) {
        free_str_array(array[i]);
    }
    free(array);
}
