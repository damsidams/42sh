/*
** EPITECH PROJECT, 2023
** my_showstr
** File description:
** bfgdbtrgjeg(hjirhn
*/

#include "my.h"

static void print_hexadecimaly(int c)
{
    int r1;
    int r2;
    char convertion_table[] = {'0', '1', '2', '3', '4', '5', '6',
        '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    my_putchar('\\');
    r1 = c % 16;
    c = c / 16;
    r2 = c % 16;
    my_putchar(convertion_table[r2]);
    my_putchar(convertion_table[r1]);
}

static int is_printable(char c)
{
    return (c >= 32 && c <= 126);
}

int my_showstr(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (is_printable(str[i]) == 0) {
            print_hexadecimaly(str[i]);
        } else
            my_putchar(str[i]);
    }
    return 0;
}
