/*
** EPITECH PROJECT, 2023
** MY_STR_ISALPHA
** File description:
** Write a function that returns 1 if the string passed
** as parameter only contains alphabetical characters
*/

#include <stdbool.h>

bool my_str_isalpha(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '_' || (str[i] > 64 && str[i] < 91) ||
            (str[i] > 96 && str[i] < 123) ||
            (str[i] > 47 && str[i] < 58))
            i++;
        else
            return false;
    }
    return true;
}
