/*
** EPITECH PROJECT, 2023
** MY LIB
** File description:
** Prints an unsigned int
*/

#include "my.h"

static int print_nb(unsigned int nb)
{
    char res;

    if (nb / 10 > 0)
        print_nb(nb / 10);
    res = (nb % 10) + '0';
    my_putchar(res);
    return 0;
}

int my_put_unbr(unsigned int nb)
{
    print_nb(nb);
    return 0;
}
