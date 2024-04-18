/*
** EPITECH PROJECT, 2023
** B-CPE-200-PAR-2-1-robotfactory-nicolas.nunney
** File description:
** my_free_n_str.c
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void my_free_n_str(int nb_of_str, ...)
{
    va_list args;
    char *str;

    va_start(args, nb_of_str);
    for (int i = 0; i < nb_of_str; ++i) {
        str = va_arg(args, char *);
        if (str != NULL)
            free(str);
    }
    va_end(args);
}
