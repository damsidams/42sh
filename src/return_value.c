/*
** EPITECH PROJECT, 2024
** lisagoulmot
** File description:
** return value
*/
#include "shell.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

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

static char *return_value(char **args, shell_info_t *my_shell)
{
    char **element = get_element(my_shell->env, args[0]);
    char *command = malloc(sizeof(char) * strlen(element[1]) + 1);

    strcpy(command, element[1]);
    return command;
}

char **check_dollar(char **args, shell_info_t *my_shell)
{
    char **args2 = my_str_to_word_array(args[1], "/");
    char *command = NULL;

    for (int i = 0; args2[i] != NULL; i++) {
        command = malloc(sizeof(char) * strlen(args2[i]) + 1);
        if (i == 0)
            strcpy(command, "/");
        if (i != 0)
            strcat(command, "/");
    printf("ok\n");
        if (strncmp(args2[i], "$", 1) == 0) {
            strcat(command,
            return_value(my_str_to_word_array(args2[i], "$"), my_shell));
            continue;
        }
        strcat(command, args2[i]);
    }
    strcpy(args[1], command);
    return args;
}
