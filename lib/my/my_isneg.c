/*
** EPITECH PROJECT, 2023
** MY_ISNEG
** File description:
** says if it is positive
*/

#include "my.h"

int my_isneg(int n)
{
    char a;
    char b;

    a = 'N';
    b = 'P';
    if (n >= 0)
        my_putchar(b);
    else
        my_putchar(a);
    my_putchar('\n');
    return (0);
}
