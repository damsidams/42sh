/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
** File description:
** command_error.c
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

void disp_err_message(char const *command)
{
    if (errno == ENOENT) {
        my_putstr_err(command);
        my_putstr_err(": Command not found.\n");
    } else if (errno == ENOEXEC) {
        my_putstr_err(command);
        my_putstr_err(": ");
        my_putstr_err(strerror(errno));
        my_putstr_err(". Wrong Architecture.\n");
    } else {
        my_putstr_err(command);
        my_putstr_err(": ");
        my_putstr_err(strerror(errno));
        my_putstr_err(".\n");
    }
}

void check_seg_fault(int wstatus, shell_info_t *my_shell)
{
    if (WIFEXITED(wstatus)) {
        my_shell->exit_status = WEXITSTATUS(wstatus);
    }
    if (WIFSIGNALED(wstatus) && WCOREDUMP(wstatus)) {
            printf("%s (core dumped)\n", strsignal(WTERMSIG(wstatus)));
            my_shell->exit_status = WTERMSIG(wstatus) + 128;
            return;
    }
    if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == 11) {
        printf("%s\n", strsignal(WTERMSIG(wstatus)));
        my_shell->exit_status = WTERMSIG(wstatus) + 128;
    }
}

void cmd_not_found(char **args, shell_info_t *my_shell,
    char *cmd_path, char **paths)
{
    if (no_env(my_shell->env)) {
        my_putstr_err(args[0]);
        my_putstr_err(": Command not found.\n");
    } else {
        disp_err_message(args[0]);
    }
    my_shell->exit_status = 1;
    free(cmd_path);
    free_str_array(paths);
    exit(1);
}
