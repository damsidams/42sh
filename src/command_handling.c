/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** command_handling.c
*/

#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "shell.h"
#include "struct.h"

void command_handling(shell_info_t *my_shell, char **args)
{
    args = check_redirect(args, my_shell);
    if (my_shell->exit_shell || !args) {
        free_str_array(args);
        return;
    }
    if (built_in_command(args, my_shell)) {
        return;
    }
    exec_cmd(args, my_shell);
}

static void exec_no_pipe(char *cmd, shell_info_t *my_shell)
{
    char **args = my_pimp_str_to_wa(cmd, " \t");

    replace_backtick(args, my_shell);
    command_handling(my_shell, args);
}

void check_cmd_type(shell_info_t *my_shell)
{
    char **cmds = get_args(my_shell);
    bool exec_status = false;

    if (cmds == NULL) {
        return;
    }
    if (!valid_redirect(cmds)) {
        my_shell->exit_status = 1;
        return;
    }
    for (unsigned int i = 0; cmds[i]; i++) {
        exec_status = check_and_or(cmds[i], my_shell);
        if (!exec_status) {
            exec_status = check_pipe(cmds[i], my_shell);
        }
        if (!exec_status) {
            exec_no_pipe(cmds[i], my_shell);
        }
    }
    free_str_array(cmds);
}

void check_given_cmd_type(shell_info_t *my_shell, char *cmd)
{
    char **cmds = my_pimp_str_to_wa(cmd, ";");
    bool exec_status = false;

    if (!cmds) {
        return;
    }
    if (!valid_redirect(cmds)) {
        my_shell->exit_status = 1;
        return;
    }
    for (unsigned int i = 0; cmds[i]; i++) {
        exec_status = check_and_or(cmds[i], my_shell);
        if (!exec_status) {
            exec_status = check_pipe(cmds[i], my_shell);
        }
        if (!exec_status) {
            exec_no_pipe(cmds[i], my_shell);
        }
    }
    free_str_array(cmds);
}
