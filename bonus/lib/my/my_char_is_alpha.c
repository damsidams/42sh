/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** my_is_alphanumeric.c
*/

#include <stdbool.h>
#include "my.h"

bool my_char_is_alpha(char c)
{
    if ((c > 47 && c < 58) || (c > 40 && c < 91) || (c > 96 && c < 123))
        return true;
    return false;
}
