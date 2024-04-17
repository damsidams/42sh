/*
** EPITECH PROJECT, 2028
** DAY3
** File description:
** Checks, if input is negative, outputs P or N accordingly
*/

#include <unistd.h>
#include "my.h"

static int print_neg(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb *= -1;
    }
    return nb;
}

static int print_nb(int nb)
{
    char res;

    if (nb / 10 > 0)
        print_nb(nb / 10);
    res = (nb % 10) + '0';
    my_putchar(res);
    return 0;
}

int my_put_nbr(int nb)
{
    nb = print_neg(nb);
    print_nb(nb);
    return 0;
}
