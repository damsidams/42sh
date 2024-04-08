/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** print_str_array.c
*/

#include "my.h"

void print_str_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++) {
        mini_printf("%s\n", array[i]);
    }
}
