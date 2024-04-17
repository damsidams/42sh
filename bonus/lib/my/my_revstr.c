/*
** EPITECH PROJECT, 2023
** MY_REVSTR
** File description:
** Write a function that reverses a string
*/

#include "my.h"

static void my_swapamoi(char *a, char *b)
{
    char stock = *b;

    *b = *a;
    *a = stock;
}

char *my_revstr(char *str)
{
    int i = my_strlen(str);
    int b = i - 1;
    int a = 0;

    if ((i % 2) == 0) {
        while (a != (b + 1)) {
            my_swapamoi(&(str[a]), &(str[b]));
            a++;
            b--;
        }
    } else {
        while (a != b) {
            my_swapamoi(&(str[a]), &(str[b]));
            a++;
            b--;
        }
    }
    return str;
}
