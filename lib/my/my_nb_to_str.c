/*
** EPITECH PROJECT, 2023
** MY_LIB
** File description:
** Transform an int into a string
*/

#include <stdlib.h>

static int get_nb_size(int *nb, int *pos)
{
    int size = 1;
    int tmp = *nb;

    if (*nb < 0) {
        *pos = 0;
        *nb *= -1;
        size++;
    }
    tmp = *nb;
    while (tmp / 10 > 0) {
        tmp /= 10;
        size++;
    }
    return size;
}

char *my_nb_to_str(int nb)
{
    int pos = 1;
    int size = get_nb_size(&nb, &pos);
    char *str_nb = malloc(sizeof(char) * (size + 1));
    int i = size;

    str_nb[i] = '\0';
    i--;
    while (i >= 0) {
        if (i == 0 && !pos)
            str_nb[i] = '-';
        if (i != 0 || pos) {
            str_nb[i] = nb % 10 + '0';
            nb /= 10;
        }
        i--;
    }
    return str_nb;
}
