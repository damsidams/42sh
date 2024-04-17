/*
** EPITECH PROJECT, 2023
** MY LIB
** File description:
** Writes the string on the err output and returns the nb of char written
*/

#include "my.h"

int my_putstr_err(char const *str)
{
    int nb_of_char = 0;

    while (str[nb_of_char] != '\0') {
        my_putchar_err(str[nb_of_char]);
        nb_of_char++;
    }
    return nb_of_char;
}
