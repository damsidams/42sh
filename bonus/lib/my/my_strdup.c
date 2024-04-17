/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** my_strdup.c
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(char *src)
{
    int i = 0;
    char *dest;

    if (!src)
        return NULL;
    dest = malloc(sizeof(char) * my_strlen(src) + 1);
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
