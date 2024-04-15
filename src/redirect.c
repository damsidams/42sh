/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell2-nicolas.nunney
** File description:
** redirect.c
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"

static void simple_output_redirect(char **args, shell_info_t *my_shell, int i)
{
    int fd;

    if (i == 0 || !args[i + 1]) {
        my_shell->exit_status = 1;
        return;
    }
    fd = open(args[i + 1], O_TRUNC | O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        my_shell->exit_status = 1;
        return;
    }
    dup2(fd, STDOUT_FILENO);
}

static void double_output_redirect(char **args, shell_info_t *my_shell, int i)
{
    int fd;

    if (i == 0 || !args[i + 1]) {
        my_shell->exit_status = 1;
        return;
    }
    fd = open(args[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        my_shell->exit_status = 1;
        return;
    }
    dup2(fd, STDOUT_FILENO);
}

static void simple_input_redirect(char **args, shell_info_t *my_shell, int i)
{
    int fd;

    if (i == 0 || !args[i + 1]) {
        my_shell->exit_status = 1;
        return;
    }
    fd = open(args[i + 1], O_RDONLY);
    if (fd == -1) {
        my_shell->exit_status = 1;
        return;
    }
    dup2(fd, STDIN_FILENO);
}

static void double_input_redirect(char **args, shell_info_t *my_shell, int i)
{
    int fd;

    if (i == 0 || !args[i + 1]) {
        my_shell->exit_status = 1;
        return;
    }
    fd = open(args[i + 1], O_RDONLY);
    if (fd == -1) {
        my_shell->exit_status = 1;
        return;
    }
    dup2(fd, STDIN_FILENO);
}

static bool file_exist(char **array)
{
    for (int i = 0; array[i]; i++) {
        if ((my_strcmp(array[i], ">>") == 0 ||
            my_strcmp(array[i], ">") == 0 ||
            my_strcmp(array[i], "<") == 0 ||
            my_strcmp(array[i], "<<") == 0) && !array[i + 1])
            return false;
    }
    return true;
}

static bool no_command(char **space_sep, char **cmd_cpy)
{
    if (file_exist(space_sep) &&
        (my_strcmp(space_sep[0], ">>") == 0 ||
        my_strcmp(space_sep[0], ">") == 0 ||
        my_strcmp(space_sep[0], "<") == 0 ||
        my_strcmp(space_sep[0], "<<") == 0)) {
        my_putstr_err("Invalid null command.\n");
        free_str_array(cmd_cpy);
        return true;
    }
    return false;
}

static bool ambiguous(char **space_sep, char **cmd_cpy)
{
    int cpt[2] = {0, 0};

    for (int i = 0; space_sep[i]; i++) {
        if (my_strcmp(space_sep[i], ">>") == 0 ||
            my_strcmp(space_sep[i], ">") == 0)
            cpt[0]++;
        if (my_strcmp(space_sep[i], "<<") == 0 ||
            my_strcmp(space_sep[i], "<") == 0)
            cpt[1]++;
    }
    if (cpt[0] > 1) {
        my_putstr_err("Ambiguous output redirect.\n");
        free_str_array(cmd_cpy);
        return true;
    } else if (cpt[1] > 1) {
        my_putstr_err("Ambiguous input redirect.");
        free_str_array(cmd_cpy);
        return true;
    }
    return false;
}

bool valid_redirect(char **cmds)
{
    char **space_sep;
    char **cmds_cpy = my_str_array_dup(cmds);

    for (int i = 0; cmds_cpy[i]; i++) {
        space_sep = my_pimp_str_to_wa(cmds_cpy[i], " ");
        if (no_command(space_sep, cmds_cpy))
            return false;
        if (!file_exist(space_sep)) {
            my_putstr_err("Missing name for redirect.\n");
            free_str_array(cmds_cpy);
            return false;
        }
        if (ambiguous(space_sep, cmds_cpy))
            return false;
        free_str_array(space_sep);
    }
    free_str_array(cmds_cpy);
    return true;
}

char **check_redirect(char **args, shell_info_t *my_shell)
{
    for (int i = 0; args[i]; i++) {
        if (my_strcmp(args[i], SIMPLE_REDIRECT_OUTPUT) == 0)
            simple_output_redirect(args, my_shell, i);
        if (my_strcmp(args[i], DOUBLE_REDIRECT_OUTPUT) == 0)
            double_output_redirect(args, my_shell, i);
        if (my_strcmp(args[i], SIMPLE_REDIRECT_INPUT) == 0)
            simple_input_redirect(args, my_shell, i);
        if (my_strcmp(args[i], DOUBLE_REDIRECT_INPUT) == 0)
            double_input_redirect(args, my_shell, i);
    }
    args = my_str_array_dup_ban_str(args, "<<");
    args = my_str_array_dup_ban_str(args, "<");
    args = my_str_array_dup_ban_str(args, ">");
    args = my_str_array_dup_ban_str(args, ">>");
    return args;
}
