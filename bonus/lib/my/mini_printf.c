/*
** EPITECH PROJECT, 2023
** mini_printf
** File description:
** You must create a function named mini_printf to learn how to use va_args
*/

#include <stdarg.h>
#include <unistd.h>
#include "my.h"

static int is_var_good(char c)
{
    if (c == 'i' || c == 'd')
        return 1;
    if (c == 's' || c == 'c')
        return 1;
    if (c == '%')
        return 1;
    return 0;
}

static int pcentage(va_list var_info, char const *format, int i)
{
    int arg_d;
    char *arg_s;
    char arg_c;
    int nb_char_print = 0;

    nb_char_print = is_var_good(format[i + 1]);
    if (format[i + 1] == 'd' || format[i + 1] == 'i') {
        arg_d = va_arg(var_info, int);
        nb_char_print = my_put_nbr(arg_d);
    }
    if (format[i + 1] == 's') {
        arg_s = va_arg(var_info, char *);
        nb_char_print = my_putstr(arg_s);
    }
    if (format[i + 1] == 'c') {
        arg_c = va_arg(var_info, int);
        nb_char_print = my_putchar(arg_c);
    }
    return nb_char_print;
}

static int is_pcent(char const *format, int i)
{
    if (format[i] == '%') {
        my_putchar('%');
        return 1;
    }
    return 0;
}

int mini_printf(char const *format, ...)
{
    int nb_char_print = 0;
    va_list var_info;

    va_start(var_info, format);
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%' && is_var_good(format[i + 1])) {
            nb_char_print += pcentage(var_info, format, i);
            i++;
            nb_char_print += is_pcent(format, i);
        } else {
            my_putchar(format[i]);
            nb_char_print ++;
        }
    }
    va_end(var_info);
    return nb_char_print;
}
