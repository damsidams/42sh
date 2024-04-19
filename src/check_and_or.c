/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Functions related to && and ||
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "shell.h"

static int get_sep_nb(char **array)
{
    int sep_nb = 0;

    for (unsigned int i = 0; array[i]; i++) {
        if (my_strcmp(array[i], "&&") == 0 || my_strcmp(array[i], "||") == 0) {
            sep_nb++;
        }
        if ((my_strcmp(array[i], "&&") == 0 || my_strcmp(array[i], "||") == 0)
            && !array[i + 1]) {
            return INVALID_NULL_COMMAND;
        }
    }
    return sep_nb;
}

static void set_array(enum sep_type *array)
{
    for (unsigned int i = 0; tmp_array[i]; i++) {
        if (my_strcmp(tmp_array[i], "&&") == 0) {
            array[index] = And;
            index++;
        }
        if (my_strcmp(tmp_array[i], "||") == 0) {
            array[index] = Or;
            index++;
        }
    }
    array[index] = NULL;
}

static enum sep_type *init_sep_array(char *cmds)
{
    char **tmp_array = my_pimp_str_to_wa(cmds, " ");
    enum sep_type *array = NULL;
    unsigned int index = 0;

    if (get_sep_nb(array) == INVALID_NULL_COMMAND) {
        free_str_array(tmp_array);
        return NULL;
    }
    array = calloc(get_sep_nb(tmp_array), sizeof(enum sep_type));
    set_array(array);
    return array;
}

static bool no_more(char **args)
{
    if (args == NULL) {
        return true;
    }
    if (my_strstrlen(args) == 1) {
        free_str_array(args);
        return true;
    }
    return false;
}

bool **check_and_or(char *cmd, shell_info_t *my_shell)
{
    char **args = my_tuned_str_to_wa(cmd, (char *[]){"&&", "||", NULL});
    enum sep_type *sep_array = NULL;

    if (no_more(args)) {
        return false;
    }
    sep_array = init_sep_array(cmds);
    if (sep_array == NULL) {
        my_putstr_err("Invalid null command.\n");
        my_shell->exit_status = 1;
        return true;
    }
}
