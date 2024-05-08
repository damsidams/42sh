/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Functions for the parentheses in 42sh
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "shell.h"

bool par_around(char const *str)
{
    if (str == NULL || strlen(str) < 2) {
        return false;
    }
    if (str[0] != '(' || str[strlen(str) - 1] != ')') {
        return false;
    }
    return true;
}

static char *rm_parentheses(char *str)
{
    char *new_str = NULL;

    if (str == NULL || strlen(str) < 2) {
        return str;
    }
    new_str = malloc(sizeof(char) * (strlen(str) - 1));
    if (new_str == NULL) {
        perror("rm_parentheses malloc failed");
        return str;
    }
    for (unsigned int i = 1; str[i] && str[i] != ')'; i++) {
        new_str[i - 1] = str[i];
    }
    new_str[strlen(str) - 2] = '\0';
    free(str);
    return new_str;
}

static bool exec_p(shell_info_t *my_shell, char *cmd)
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

bool exec_parentheses(shell_info_t *my_shell, char **args)
{
    if (args == NULL) {
        return false;
    }
    for (unsigned int i = 0; args[i]; i++) {
        if (par_around(args[i])) {
            args[i] = rm_parentheses(args[i]);
            exec_p(my_shell, args[i]);
            free(args[i]);
            args[i] = strdup(MAGIC_STRING);
        }
    }
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

static bool p_check(char const *cmd)
{
    char **line = my_pimp_str_to_wa(cmd, " ");

    if (line == NULL || cmd == NULL) {
        return true;
    }
    if (my_strstrlen(line) <= 1) {
        return false;
    }
    for (unsigned int i = 1; line[i]; i++) {
        if (is_parentheses(line[i])) {
            dprintf(2, "Badly placed ()'s.\n");
            free_str_array(line);
            return true;
        }
    }
    free_str_array(line);
    return false;
}

bool parentheses_badly_placed(char const *cmd)
{
    char **cmds = my_pimp_str_to_wa(cmd, ";");

    for (unsigned int i = 0; cmds[i]; i++) {
        if (p_check(cmds[i])) {
            free_str_array(cmds);
            return true;
        }
    }
    free_str_array(cmds);
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
