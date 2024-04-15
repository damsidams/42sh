/*
** EPITECH PROJECT, 2023
** MY_GETNUMBER
** File description:
** return a number hide in a string
*/

#include "my.h"

static int isitover(char const *str, int i)
{
    if (str[i + 1] < '0' || str[i + 1] > '9') {
        return 0;
    }
    return 1;
}

static int ispos(char const *str, int i, int pos)
{
    if (i != 0) {
        if (str[i - 1] == '-') {
            pos = -1;
        }
    }
    return pos;
}

static int retourforce(int nb, int istolong)
{
    if (nb < 0)
        return 0;
    return istolong;
}

static int addnb(char const *str, int i, int nb)
{
    int x;

    x = str[i] - 48;
    nb = nb * 10 + x;
    return nb;
}

int my_special_getnbr(char const *str)
{
    int pos = 1;
    int nb = 0;
    int istolong = 1;
    int isover = 1;
    int tnum = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        while (str[i] >= '0' && str[i] <= '9' && isover == 1) {
            pos = ispos(str, i, pos);
            nb = addnb(str, i, nb);
            isover = isitover(str, i);
            istolong = retourforce(nb, istolong);
            i++;
            tnum++;
        }
        istolong = retourforce(nb, istolong);
        if (pos == 0)
            nb = nb * (-1);
    }
    return nb * istolong * pos;
}
