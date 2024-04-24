/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Functions related to time
*/

#include <time.h>
#include <stdlib.h>
#include "shell.h"

static char *get_min_time(int min)
{
    char *zero = NULL;
    char *char_min = my_nb_to_str(min);
    char *ret = NULL;

    if (min < 10) {
        zero = my_strdup("0");
        ret = my_strcat(zero, char_min);
        free(zero);
        free(char_min);
        return ret;
    }
    return char_min;
}

char *get_current_time(void)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *h = my_nb_to_str(tm.tm_hour);
    char *min = get_min_time(tm.tm_min);
    char *ret = my_strcat(h, ":");
    char *f_ret = my_strcat(ret, min);

    free(h);
    free(min);
    free(ret);
    return f_ret;
}
