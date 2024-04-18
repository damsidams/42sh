/*
** EPITECH PROJECT, 2023
** MY_PUTSTR
** File description:
** Write a function that displays the characters of a string
*/

#include "my.h"

int my_putstr(char const *str)
{
    int i;

    i = 0;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i = i + 1;
    }
    return 0;
}

int my_putstr_no_break(char const *str)
{
    int i;

    i = 0;
    while (str[i] != '\n' && str[i] != '\0') {
        my_putchar(str[i]);
        i = i + 1;
    }
    return 0;
}
