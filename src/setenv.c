/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** setenv.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "my.h"
#include "struct.h"

static char **replace_value(char **env, int index,
    char const *name, char const *value)
{
    char *new_name = my_strcat(name, "=");
    char *name_value = my_strcat(new_name, value);

    free(env[index]);
    env[index] = my_strdup(name_value);
    free(new_name);
    free(name_value);
    return env;
}

static char **add_new_name(char **env, char const *name, char **temp_env)
{
    char *new_name = my_strcat(name, "=");

    free_str_array(env);
    env = malloc(sizeof(char *) * (my_strstrlen(temp_env) + 2));
    if (env == NULL) {
        perror("add_new_name malloc failed");
    }
    for (int i = 0; i != my_strstrlen(temp_env) + 2; i++) {
        env[i] = NULL;
    }
    env = my_str_array_cpy(temp_env, env);
    env[my_strstrlen(temp_env)] = my_strdup(new_name);
    free_str_array(temp_env);
    free(new_name);
    return env;
}

static char **add_new_name_value(char **env,
    char const *name, char const *value)
{
    char *new_name = my_strcat(name, "=");
    char *new_value = my_strcat(new_name, value);
    char **temp_env = my_str_array_dup(env);

    free_str_array(env);
    env = malloc(sizeof(char *) * (my_strstrlen(temp_env) + 2));
    for (int i = 0; i != my_strstrlen(temp_env) + 2; i++)
        env[i] = NULL;
    env = my_str_array_cpy(temp_env, env);
    env[my_strstrlen(temp_env)] = my_strdup(new_value);
    env[my_strstrlen(temp_env) + 1] = NULL;
    free(new_value);
    free(new_name);
    free_str_array(temp_env);
    return env;
}

char **set_name(char const *name, shell_info_t *my_shell)
{
    char *env_name = NULL;
    char **temp_env = my_str_array_dup(my_shell->env);
    char *new_name = my_strcat(name, "=");

    for (int i = 0; (my_shell->env)[i]; i++) {
        env_name = get_name(my_shell->env, i);
        if (my_strcmp(name, env_name) == 0) {
            free((my_shell->env)[i]);
            (my_shell->env)[i] = my_strdup(new_name);
            free(env_name);
            free_str_array(temp_env);
            free(new_name);
            return my_shell->env;
        }
        free(env_name);
    }
    free(new_name);
    my_shell->env = add_new_name(my_shell->env, name, temp_env);
    my_shell->exit_status = 0;
    return my_shell->env;
}

char **set_name_value(char const *name,
    char const *value, shell_info_t *my_shell)
{
    char *env_name = NULL;

    for (int i = 0; (my_shell->env)[i]; i++) {
        env_name = get_name(my_shell->env, i);
        if (my_strcmp(name, env_name) == 0) {
            my_shell->env = replace_value(my_shell->env, i, name, value);
            free(env_name);
            return my_shell->env;
        }
        free(env_name);
    }
    my_shell->env = add_new_name_value(my_shell->env, name, value);
    return my_shell->env;
}

void set_env_no_disp(char **args, shell_info_t *my_shell)
{
    char *name = NULL;
    char *value = NULL;

    if (my_strstrlen(args) > 3) {
        my_putstr_err("setenv: Too many arguments.\n");
        my_shell->exit_status = 1;
        return;
    }
    if (my_strstrlen(args) >= 2) {
        name = my_strdup(args[1]);
        if (my_strstrlen(args) == 3) {
            value = my_strdup(args[2]);
            my_shell->env = set_name_value(name, value, my_shell);
            free(value);
        } else {
            my_shell->env = set_name(name, my_shell);
        }
        free(name);
    }
    my_shell->exit_status = 0;
}

static bool is_valid_arg(char *arg)
{
    if (!my_str_isalpha(arg)) {
        my_putstr_err("setenv: Variable name must contain ");
        my_putstr_err("alphanumeric characters.\n");
        return false;
    }
    if ((arg[0] < 65 || arg[0] > 91) && ((arg[0] < 97 || arg[0] > 122))) {
        my_putstr_err("setenv: Variable name must begin with a letter.\n");
        return false;
    }
    return true;
}

static bool arg_error(char **args)
{
    if (my_strstrlen(args) > 3) {
        my_putstr_err("setenv: Too many arguments.\n");
        return true;
    }
    if (my_strstrlen(args) == 2 && !is_valid_arg(args[1])) {
        return true;
    }
    if (my_strstrlen(args) == 3 && !is_valid_arg(args[1])) {
        return true;
    }
    return false;
}

static bool check_exceptions(char **args, shell_info_t *my_shell)
{
    if (my_strstrlen(my_shell->env) == 0) {
        return true;
    }
    if (my_strstrlen(args) == 1) {
        print_str_array(my_shell->env);
        return true;
    }
    if (my_strstrlen(args) >= 2 && arg_error(args)) {
        my_shell->exit_status = 1;
        return true;
    }
    return false;
}

void set_env(char **args, shell_info_t *my_shell)
{
    char *name = NULL;
    char *value = NULL;

    if (check_exceptions(args, my_shell)) {
        return;
    }
    if (my_strstrlen(args) >= 2) {
        name = my_strdup(args[1]);
        if (my_strstrlen(args) == 3) {
            value = my_strdup(args[2]);
            my_shell->env = set_name_value(name, value, my_shell);
            free(value);
        } else {
            my_shell->env = set_name(name, my_shell);
        }
        free(name);
    }
    my_shell->exit_status = 0;
}
