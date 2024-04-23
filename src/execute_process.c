/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** All function for executing processes.
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

static void disp_err_message(char const *command)
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

static char **get_paths(char **env)
{
    int i = 0;

    if (!env || my_strstrlen(env) == 0) {
        return NULL;
    }
    while (env[i] && my_strncmp(env[i], "PATH", 4) != 0) {
        i++;
    }
    return my_pimp_str_to_wa(env[i], ":=");
}

static void cmd_not_found(char **args, shell_info_t *my_shell,
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

static bool is_ampersand(char **args)
{
    for (int i = 0; args[i]; i++) {
        if (my_strcmp(args[i], "&") == 0) {
            return true;
        }
    }
    return false;
}

static void default_signals(void)
{
    setpgid(0, 0);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
}

static bool exec_bin_paths(char **cmd_path, char **args,
    shell_info_t *my_shell)
{
    char **paths = get_paths(my_shell->env);
    bool command_found = false;

    for (int i = 1; paths && paths[i]; i++) {
        if (*cmd_path)
            free(*cmd_path);
        *cmd_path = my_strcat(paths[i], "/");
        *cmd_path = my_strcat(*cmd_path, args[0]);
        if (*cmd_path && execve(*cmd_path, args, my_shell->env) != -1) {
            command_found = true;
            break;
        }
    }
    return command_found;
}

static void exec_paths(char **args, shell_info_t *my_shell)
{
    char **paths = get_paths(my_shell->env);
    char *cmd_path = NULL;
    bool command_found = false;

    default_signals();
    command_found = exec_bin_paths(&cmd_path, args, my_shell);
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
    bool ampersand = is_ampersand(args);

    if (ampersand)
        args = my_word_array_delete(args, "&");
    child = fork();
    if (child == 0) {
        exec_paths(args, my_shell);
    } else {
        if (!ampersand) {
            wait_for_pid(child, my_shell);
        } else {
            add_job(child, my_shell, false);
        }
    }
    free_str_array(args);
}
