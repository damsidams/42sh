/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** my_str_array_cpy.c
*/

#include "my.h"

char **my_str_array_cpy(char **array, char **array_cpy)
{
    for (int i = 0; array[i]; i++)
        array_cpy[i] = my_strdup(array[i]);
    return array_cpy;
}
