/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** command_handling.c
*/

#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "my.h"
#include "shell.h"
#include "struct.h"

static void exec_good_type(char *cmd, shell_info_t *my_shell)
{
    bool exec_status = check_and_or(cmd, my_shell);
    char **word_array = my_str_to_word_array(cmd, " ");
    
    if (!exec_status) {
        exec_status = check_pipe(cmd, my_shell);
    }
    if (!exec_status) {
        if (get_globbing_nb(word_array) != 0) {
            globbing(word_array, my_shell);
            exec_status = true;
        }
    }
    if (!exec_status) {
        exec_no_pipe(cmd, my_shell);
    }
    free_str_array(word_array);
}

void check_cmd_type(shell_info_t *my_shell)
{
    char **cmds = get_args(my_shell);

    if (cmds == NULL) {
        return;
    }
    cmds = replace_backtick(cmds, my_shell);
    if (cmds == NULL) {
        return;
    }
    if (!valid_redirect(cmds)) {
        my_shell->exit_status = 1;
        free_str_array(cmds);
        return;
    }
    for (unsigned int i = 0; cmds[i]; i++) {
        exec_good_type(cmds[i], my_shell);
    }
    free_str_array(cmds);
}

void check_given_cmd_type(shell_info_t *my_shell, char *cmd)
{
    char **cmds = NULL;

    cmd = check_if_historic(&cmd, my_shell);
    if (cmd == NULL) {
        return;
    }
    cmds = my_pimp_str_to_wa(cmd, ";");
    cmds = replace_backtick(cmds, my_shell);
    if (!cmds) {
        return;
    }
    if (!valid_redirect(cmds)) {
        my_shell->exit_status = 1;
        return;
    }
    for (unsigned int i = 0; cmds[i]; i++) {
        exec_good_type(cmds[i], my_shell);
    }
    free_str_array(cmds);
}
