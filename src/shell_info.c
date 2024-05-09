/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Function to copy the struct shell_info
*/

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "shell.h"

int end_shell(shell_info_t *my_shell)
{
    int return_value = 0;

    if (my_shell->env) {
        free_str_array(my_shell->env);
    }
    free(my_shell->last_path);
    free(my_shell->color);
    end_job_control(my_shell);
    return_value = my_shell->exit_status;
    free(my_shell);
    return return_value;
}

void set_shell_pgid(shell_info_t *my_shell)
{
    if (!my_shell->is_a_tty) {
        return;
    }
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, sigstp_handler);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    my_shell->shell_pgid = getpid();
    setpgid(my_shell->shell_pgid, my_shell->shell_pgid);
    tcsetpgrp(STDIN_FILENO, my_shell->shell_pgid);
    signal_child(my_shell->shell_pgid, 0, my_shell);
    my_shell->last_cmd = NULL;
}

static shell_info_t *set_shell_info(shell_info_t *my_shell)
{
    my_shell->last_path = NULL;
    my_shell->exit_status = 0;
    my_shell->exit_shell = false;
    my_shell->jobs = NULL;
    my_shell->shell_pgid = 0;
    my_shell->color = malloc(sizeof(int) * 2);
    set_shell_pgid(my_shell);
    my_shell->stopped_pid = my_shell->shell_pgid;
    my_shell->jobs = NULL;
    if (my_shell->color == NULL) {
        perror("shell color malloc");
    } else {
        my_shell->color[0] = valid_color(DEFAULT_SUCCESS_COLOR);
        my_shell->color[1] = valid_color(DEFAULT_ERROR_COLOR);
    }
    return my_shell;
}

shell_info_t *init_shell_info_t(char **env)
{
    shell_info_t *my_shell = malloc(sizeof(shell_info_t));

    if (my_shell == NULL) {
        perror("init_shell_info malloc");
        return NULL;
    }
    if (!env || my_strstrlen(env) == 0)
        my_shell->env = NULL;
    else {
        my_shell->env = my_str_array_dup(env);
    }
    if (isatty(STDIN_FILENO))
        my_shell->is_a_tty = true;
    else
        my_shell->is_a_tty = false;
    my_shell->stdin_cpy = dup(STDIN_FILENO);
    my_shell->stdout_cpy = dup(STDOUT_FILENO);
    my_shell->list_alias = NULL;
    my_shell->local = NULL;
    return set_shell_info(my_shell);
}
