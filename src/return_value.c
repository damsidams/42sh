/*
** EPITECH PROJECT, 2024
** lisagoulmot
** File description:
** return value
*/
#include "shell.h"
#include <stddef.h>

static char **get_element(char **env, char *element)
{
    int i = 0;

    if (!env || my_strstrlen(env) == 0) {
        return NULL;
    }
    while (env[i] && my_strncmp(env[i], element, strlen(element)) != 0) {
        i++;
    }
    return my_str_to_word_array(env[i], "=");
}

static char *check_dollar(char **args, shell_info_t *my_shell)
{
    char **args2 = my_str_to_word_array(args[1], "/");
    char *command = NULL;

    for (int i = 0; args2[i] != NULL; i++) {
        if (i == 0)
            strcpy(command, "/");
        if (i != 0)
            strcat(command, "/");
        if (strncmp(args2[i], "$", 1) == 0) {
            strcat(command, return_value(args2[i], my_shell->env));
            continue;
        }
        strcat(command, args2[i]);
    }
    return command;
}

char *return_value(char *args, shell_info_t *my_shell)
{
}
