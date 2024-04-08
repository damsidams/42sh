/*
** EPITECH PROJECT, 2023
** MY_STRCAPITALIZE
** File description:
** Write a function that capitalizes the first letter of each word
*/

#include "my.h"

static char *editstr(char *str, int i)
{
    if (str[i] > 96 && str[i] < 123)
        str[i] = str[i] - 32;
    return str;
}

char *my_strcapitalize(char *str)
{
    my_strlowcase(str);
    if (str[0] > 96 && str[0] < 123) {
        if (str[0] > 96 && str[0] < 123)
            str[0] = str[0] - 32;
    }
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i - 1] == ' ' || str[i - 1] == '-' || str[i - 1] == '+') {
            str = editstr(str, i);
        }
    }
    return str;
}
