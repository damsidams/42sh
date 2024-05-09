/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** cd.c
*/

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "my.h"
#include "struct.h"

static char *get_current_path(void)
{
    char *path = NULL;

    path = getcwd(path, BUFSIZ);
    return path;
}

static void set_pwd(shell_info_t *my_shell)
{
    char *new_path = get_current_path();
    char *args[] = {"setenv", "PWD", new_path, NULL};

    if (my_shell->env) {
        set_env(args, my_shell);
    }
    free(new_path);
}

static char *get_home(char **env)
{
    char **line = NULL;
    char *home = NULL;

    if (!env || my_strstrlen(env) == 0) {
        return NULL;
    }
    for (int i = 0; env[i]; i++) {
        line = my_str_to_word_array(env[i], "=");
        if (strcmp("HOME", line[0]) == 0) {
            home = strdup(line[1]);
            free_str_array(line);
            return home;
        }
        free_str_array(line);
    }
    return NULL;
}

static void goto_last_dir(shell_info_t *my_shell)
{
    char *temp_last_path = NULL;

    temp_last_path = getcwd(temp_last_path, BUFSIZ);
    chdir(my_shell->last_path);
    if (my_shell->last_path) {
        mini_printf("%s\n", my_shell->last_path);
        free(my_shell->last_path);
    }
    my_shell->last_path = my_strdup(temp_last_path);
    free(temp_last_path);
    set_pwd(my_shell);
    my_shell->exit_status = 0;
}

void goto_root(shell_info_t *my_shell)
{
    char *home = NULL;

    if (my_shell->last_path) {
        free(my_shell->last_path);
    }
    my_shell->last_path = NULL;
    my_shell->last_path = getcwd(my_shell->last_path, BUFSIZ);
    home = get_home(my_shell->env);
    if (!home) {
        chdir("/home");
    } else {
        chdir(home);
    }
    set_pwd(my_shell);
    my_shell->exit_status = 0;
    if (home)
        free(home);
}

void goto_dir(shell_info_t *my_shell, char const *path)
{
    int valid_path = 0;
    char *temp_last_path = NULL;

    temp_last_path = getcwd(temp_last_path, BUFSIZ);
    valid_path = chdir(path);
    if (valid_path == -1) {
        my_putstr_err(path);
        my_putstr_err(": ");
        my_putstr_err(strerror(errno));
        my_putstr_err(".\n");
        free(temp_last_path);
        my_shell->exit_status = 1;
        return;
    }
    set_pwd(my_shell);
    my_shell->last_path = my_strdup(temp_last_path);
    free(temp_last_path);
    set_pwd(my_shell);
    my_shell->exit_status = 0;
}

void change_dir(char **args, shell_info_t *my_shell)
{
    if (my_strstrlen(args) > 2) {
        my_putstr_err("my_sh: cd: too many arguments\n");
        my_shell->exit_status = 1;
        return;
    }
    if (my_strstrlen(args) == 1 || (my_strstrlen(args) == 2 &&
        my_strcmp(args[1], "~") == 0)) {
        goto_root(my_shell);
        return;
    }
    if (my_strstrlen(args) == 2 && my_strcmp(args[1], "-") == 0) {
        if (my_shell->last_path) {
            goto_last_dir(my_shell);
            return;
        }
        my_putstr_err("mysh: cd: OLDPWD not set\n");
        my_shell->exit_status = 1;
        return;
    }
    goto_dir(my_shell, args[1]);
}
