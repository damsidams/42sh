/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Functions for the parentheses in 42sh
*/

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "shell.h"

bool exec_parentheses(shell_info_t *my_shell, char *cmd)
{
    shell_info_t *shell_copy = init_shell_info_t(my_shell->env);

    if (shell_copy == NULL) {
        return false;
    }
    check_given_cmd_type(shell_copy, cmd);
    my_shell->exit_status = shell_copy->exit_status;
    end_shell(shell_copy);
    return true;
}

static bool is_parentheses(char const *str)
{
    for (unsigned int i = 0; str[i]; i++) {
        if (str[i] == '(' || str[i] == ')') {
            return true;
        }
    }
    return false;
}

bool parentheses_badly_placed(char const *cmd)
{
    char **line = my_pimp_str_to_wa(cmd, " ");

    if (line == NULL) {
        return true;
    }
    if (my_strstrlen(line) <= 1) {
        return false;
    }
    for (unsigned int i = 0; line[i]; i++) {
        if (is_parentheses(line[i])) {
            dprintf(2, "Badly placed ()'s.\n");
            free_str_array(line);
            return true;
        }
    }
    free_str_array(line);
    return false;
}

bool check_parentheses_order(char const *str)
{
    int nb = 0;

    for (unsigned int i = 0; str[i]; i++) {
        if (str[i] == '(') {
            nb++;
        }
        if (str[i] == ')') {
            nb--;
        }
        if (nb < 0) {
            dprintf(2, "Too many )'s.\n");
            return false;
        }
    }
    if (nb == 0) {
        return true;
    }
    dprintf(2, "Too many ('s.\n");
    return false;
}
