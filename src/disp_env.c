/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** disp_env.c
*/

#include <stddef.h>
#include "shell.h"
#include "my.h"
#include "struct.h"

bool no_env(char **env)
{
    char **equal_sep = NULL;

    if (my_strstrlen(env) == 0)
        return true;
    for (int i = 0; env[i]; i++) {
        equal_sep = my_pimp_str_to_wa(env[i], "=");
        if (my_strcmp(equal_sep[0], "PATH") == 0 &&
            my_strlen(equal_sep[1]) != 0) {
            free_str_array(equal_sep);
            return false;
        }
        free_str_array(equal_sep);
    }
    return false;
}

void disp_env(char **args, shell_info *my_shell)
{
    (void)args;
    print_str_array(my_shell->env);
    my_shell->exit_status = 0;
}
