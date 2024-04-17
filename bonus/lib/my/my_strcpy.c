/*
** EPITECH PROJECT, 2023
** MY_STRCPY
** File description:
** Write a function that copies a string into another
*/

#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int pos = 0;

    if (src[pos] == '\0') {
        dest[pos] = '\0';
        return dest;
    }
    for (int i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
        pos = i;
    }
    dest[pos + 1] = '\0';
    return dest;
}
