/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Functions for the parentheses in 42sh
*/

#include <stdbool.h>
#include "shell.h"

bool exec_parentheses(shell_info_t *my_shell, char *cmd)
{
    shell_info_t *shell_copy = init_shell_info_t(my_shell->env);

    if (shell_copy == NULL) {
        return false;
    }
    check_given_cmd_type(shell_copy, cmd);
    my_shell->return_value = shell_copy->return_value;
    end_shell(shell_copy);
    return true;
}
