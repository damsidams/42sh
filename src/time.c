/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Functions related to time
*/

#include <time.h>
#include <stdlib.h>
#include "shell.h"

char *get_current_time(void)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *h = my_nb_to_str(tm.tm_hour);
    char *min = my_nb_to_str(tm.tm_min);
    char *ret = my_strcat(h, ":");
    char *f_ret = my_strcat(ret, min);

    free(h);
    free(min);
    free(ret);
    return f_ret;
}
