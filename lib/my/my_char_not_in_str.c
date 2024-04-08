/*
** EPITECH PROJECT, 2023
** B-CPE-200-PAR-2-1-robotfactory-nicolas.nunney
** File description:
** my_char_not_in_str.c
*/

#include <stdbool.h>
#include "my.h"

bool my_char_in_str(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (c == str[i])
            return true;
    }
    return false;
}
