/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** unsetenv.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "minishell1.h"
#include "my.h"
#include "struct.h"

static int get_name_len(char **env, int i)
{
    int len = 0;
    int j = 0;

    while (env[i][j] != '=') {
        len++;
        j++;
    }
    return len;
}

char *get_name(char **env, int index)
{
    char *name = malloc(sizeof(char) * get_name_len(env, index) + 1);

    for (int j = 0; env[index][j] != '='; j++)
        name[j] = env[index][j];
    name[get_name_len(env, index)] = '\0';
    return name;
}

char **remove_var(char **env, int index)
{
    char **new_env = malloc(sizeof(char *) * my_strstrlen(env));
    int j = 0;

    for (int i = 0; env[i]; i++) {
        if (i != index) {
            new_env[j] = my_strdup(env[i]);
            j++;
        }
    }
    new_env[j] = NULL;
    free_str_array(env);
    return new_env;
}

static void check_existence(shell_info *my_shell, char *name)
{
    char *env_name = NULL;

    for (int i = 0; (my_shell->env)[i]; i++) {
        env_name = get_name(my_shell->env, i);
        if (my_strcmp(name, env_name) == 0) {
            my_shell->env = remove_var(my_shell->env, i);
            break;
        }
        free(env_name);
        env_name = NULL;
    }
    if (env_name)
        free(env_name);
}

void unset_env(char **args, shell_info *my_shell)
{
    char *name;

    if (my_strstrlen(my_shell->env) == 0)
        return;
    if (my_strstrlen(args) < 2) {
        my_putstr_err("unsetenv: Too few arguments.\n");
        my_shell->exit_status = 1;
        return;
    }
    for (int i = 1; args[i]; i++) {
        name = my_strdup(args[i]);
        check_existence(my_shell, name);
        free(name);
    }
    my_shell->exit_status = 0;
}
