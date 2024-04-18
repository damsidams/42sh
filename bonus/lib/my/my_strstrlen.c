/*
** EPITECH PROJECT, 2023
** MY LIB
** File description:
** Returns the lengh of a string of string
*/

#include <stdlib.h>

int my_strstrlen(char **str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len] != NULL)
        len++;
    return len;
}
