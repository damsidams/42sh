/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell2-nicolas.nunney
** File description:
** pipe.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "struct.h"

char **get_pipe_cmds(char *cmd)
{
    char *cmd_cpy = my_strdup(cmd);
    char **pipe_sep = my_pimp_str_to_wa(cmd_cpy, "|");

    print_str_array(pipe_sep);
    if (my_strstrlen(pipe_sep) == 1) {
        printf("no pipe\n");
        free(cmd_cpy);
        free_str_array(pipe_sep);
        return NULL;
    }
    free(cmd_cpy);
    return pipe_sep;
}

static void exec_last_cmd(char **cmd_args, shell_info_t *my_shell, int *pipefd)
{
    dup2(pipefd[0], STDIN_FILENO);
    dup2(my_shell->stdout_cpy, STDOUT_FILENO);
    close(pipefd[1]);
    command_handling(my_shell, cmd_args);
}

static void exec_pipe(char **args, shell_info_t *my_shell, int i, int *pipefd)
{
    char **cmd_args = my_pimp_str_to_wa(args[i], " ");

    replace_backtick(cmd_args, my_shell);
    if (i == my_strstrlen(args) - 1)
        exec_last_cmd(cmd_args, my_shell, pipefd);
    else {
        pipe(pipefd);
        if (fork() == 0) {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            command_handling(my_shell, cmd_args);
            close(pipefd[1]);
            exit(EXIT_SUCCESS);
        } else {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            exec_pipe(args, my_shell, i + 1, pipefd);
        }
    }
}

static bool check_null_cmd(char *cmd, char **pipe_sep)
{
    int pipe_cpt = 0;

    for (int i = 0; cmd[i] != '\0'; i++) {
        if (cmd[i] == '|')
            pipe_cpt++;
    }
    if (pipe_cpt == 0) {
        return false;
    }
    if (pipe_cpt != my_strstrlen(pipe_sep) - 1) {
        return true;
    }
    return false;
}

bool check_pipe(char *cmd, shell_info_t *my_shell)
{
    char **pipe_sep = get_pipe_cmds(cmd);
    int stdout_cpy = dup(STDOUT_FILENO);
    int stdin_cpy = dup(STDIN_FILENO);
    int pipefd[2];

    if (!pipe_sep && !check_null_cmd(cmd, pipe_sep)) {
        return false;
    }
    if (check_null_cmd(cmd, pipe_sep)) {
        my_putstr_err("Invalid null command.\n");
        my_shell->exit_status = 1;
        return true;
    }
    exec_pipe(pipe_sep, my_shell, 0, pipefd);
    dup2(stdout_cpy, STDOUT_FILENO);
    dup2(stdin_cpy, STDIN_FILENO);
    free_str_array(pipe_sep);
    return true;
}
