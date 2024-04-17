/*
** EPITECH PROJECT, 2023
** MY_FIND_PRIME_SUP
** File description:
** smallest prime number that is greater
*/

#include "my.h"

int my_find_prime_sup(int nb)
{
    int found = 0;

    while (found != 1) {
        if (my_is_prime(nb) == 1)
            return nb;
        if ((nb + 1) < nb)
            return 0;
        nb++;
    }
    return 0;
}
