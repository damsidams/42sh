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

static void default_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
}

static bool is_ampersand(char **args)
{
    for (int i = 0; args[i]; i++) {
        if (my_strcmp(args[i], "&") == 0) {
            return true;
        }
    }
    return false;
}

static void free_paths(char *cmd_path, char **paths)
{
    free(cmd_path);
    free_str_array(paths);
}

static void exec_paths(char **args, shell_info_t *my_shell)
{
    char **paths = get_paths(my_shell->env);
    char *cmd_path = NULL;
    bool command_found = false;

    default_signals();
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
    free_paths(cmd_path, paths);
}

static void foreground_background_handle(pid_t child, bool ampersand,
    char **args, shell_info_t *my_shell)
{
    process_t *process = NULL;

    setpgid(child, child);
    if (!ampersand) {
        wait_for_pid(child, my_shell);
    } else {
        process = add_job(child, my_shell, args[0]);
        process->is_background = true;
    }
}

static void job_control_setup(char **args, bool ampersand,
    shell_info_t *my_shell)
{
    if (my_shell->last_cmd) {
        free(my_shell->last_cmd);
        my_shell->last_cmd = NULL;
    }
    my_shell->last_cmd = strdup(args[0]);
    if (ampersand)
        args = my_word_array_delete(args, "&");
}

void exec_cmd(char **args, shell_info_t *my_shell)
{
    pid_t child;
    bool ampersand = is_ampersand(args);

    if (!args || !args[0] || strcmp(args[0], MAGIC_STRING) == 0) {
        return;
    }
    job_control_setup(args, ampersand, my_shell);
    child = fork();
    if (child == 0) {
        setpgid(getpid(), getpid());
        if (!ampersand)
            tcsetpgrp(STDIN_FILENO, -getpid());
        exec_paths(args, my_shell);
    } else {
        foreground_background_handle(child, ampersand, args, my_shell);
    }
    free_str_array(args);
}

void command_handling(shell_info_t *my_shell, char **args)
{
    args = replace_var(args, my_shell);
    if (!args) {
        my_shell->exit_status = 1;
        return;
    }
    args = check_redirect(args, my_shell);
    exec_parentheses(my_shell, args);
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
