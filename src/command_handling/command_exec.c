/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
** File description:
** command_exec.c
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

char **get_paths(char **env)
{
    int i = 0;

    if (!env || my_strstrlen(env) == 0) {
        return NULL;
    }
    while (env[i] && my_strncmp(env[i], "PATH", 4) != 0) {
        i++;
    }
    if (env[i] == NULL) {
        return NULL;
    }
    return my_pimp_str_to_wa(env[i], ":=");
}

static void exec_paths(char **args, shell_info_t *my_shell)
{
    char **paths = get_paths(my_shell->env);
    char *cmd_path = NULL;
    bool command_found = false;

    for (int i = 1; paths && paths[i]; i++) {
        if (cmd_path)
            free(cmd_path);
        cmd_path = my_strcat(paths[i], "/");
        cmd_path = my_strcat(cmd_path, args[0]);
        if (cmd_path && execve(cmd_path, args, my_shell->env) != -1) {
            command_found = true;
            break;
        }
    }
    if (my_strstrlen(my_shell->env) == 0 || (cmd_path && !command_found &&
        execve(args[0], args, my_shell->env) == -1)) {
        cmd_not_found(args, my_shell, cmd_path, paths);
    }
    free(cmd_path);
    free_str_array(paths);
}

void exec_cmd(char **args, shell_info_t *my_shell)
{
    pid_t child;
    int wstatus = 0;

    if (is_dollar(args[1]) == 1) {
        printf("%s\n", args[1]);
        args = check_dollar(args, my_shell);
    }
    child = fork();
    if (child == 0) {
        exec_paths(args, my_shell);
    } else {
        waitpid(child, &wstatus, 0);
        check_seg_fault(wstatus, my_shell);
    }
    free_str_array(args);
}

void command_handling(shell_info_t *my_shell, char **args)
{
    args = check_redirect(args, my_shell);
    if (my_shell->exit_shell || !args) {
        free_str_array(args);
        return;
    }
    if (built_in_command(args, my_shell) || exec_alias(my_shell, args[0])) {
        return;
    }
    exec_cmd(args, my_shell);
}

void exec_no_pipe(char *cmd, shell_info_t *my_shell)
{
    char **args = my_pimp_str_to_wa(cmd, " \t");

    command_handling(my_shell, args);
}
