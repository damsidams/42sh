/*
** EPITECH PROJECT, 2023
** MY LIB
** File description:
** Writes a char in the err output
*/

#include <unistd.h>

int my_putchar_err(char c)
{
    write(2, &c, 1);
    return 1;
}
