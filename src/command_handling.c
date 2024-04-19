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

static void check_seg_fault(int wstatus, shell_info_t *my_shell)
{
    if (WIFEXITED(wstatus)) {
        my_shell->exit_status = WEXITSTATUS(wstatus);
    }
    if (WIFSIGNALED(wstatus) && WCOREDUMP(wstatus)) {
            mini_printf("%s (core dumped)\n", strsignal(WTERMSIG(wstatus)));
            my_shell->exit_status = WTERMSIG(wstatus) + 128;
            return;
    }
    if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == 11) {
        mini_printf("%s\n", strsignal(WTERMSIG(wstatus)));
        my_shell->exit_status = WTERMSIG(wstatus) + 128;
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
    if (built_in_command(args, my_shell)) {
        return;
    }
    exec_cmd(args, my_shell);
}

static void exec_no_pipe(char *cmd, shell_info_t *my_shell)
{
    char **args = my_pimp_str_to_wa(cmd, " \t");

    command_handling(my_shell, args);
}

void check_cmd_type(shell_info_t *my_shell)
{
    char **cmds = NULL;
    bool pipe_status = false;

    cmds = get_args(my_shell);
    if (cmds == NULL) {
        return;
    }
    if (!valid_redirect(cmds)) {
        my_shell->exit_status = 1;
        return;
    }
    for (int i = 0; cmds[i]; i++) {
        pipe_status = check_pipe(cmds[i], my_shell);
        if (!pipe_status) {
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
    for (int i = 0; cmds[i]; i++) {
        exec_status = check_and_or(cmds[i]);
        if (!exec_status) {
            exec_status = check_pipe(cmds[i], my_shell);
        }
        if (!exec_status) {
            exec_no_pipe(cmds[i], my_shell);
        }
    }
    free_str_array(cmds);
}
