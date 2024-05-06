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
        if (env[i + 1] == NULL &&
            my_strncmp(env[i], element, strlen(element)) != 0)
            return NULL;
        i++;
    }
    return my_str_to_word_array(env[i], "=");
}

static char *return_value(char **args, shell_info_t *my_shell)
{
    char **element = get_element(my_shell->env, args[0]);
    char *command = NULL;

    if (element == NULL) {
        printf("%s: Undefined variable.", args[0]);
        return NULL;
    }
    command = malloc(sizeof(char) * strlen(element[1]) + 1);
    strcpy(command, element[1]);
    return command;
}

char **check_dollar(char **args, shell_info_t *my_shell)
{
    char **args2 = my_str_to_word_array(args[1], "/");
    char *command = NULL;
    int lengh = 0;

    for (int i = 0; args2[i] != NULL; i++) {
        if (strncmp(args2[i], "$", 1) == 0) {
            lengh = strlen(return_value(my_str_to_word_array(args2[i], "$")
                , my_shell) + 2);
            command = malloc((sizeof(char) * lengh));
            strcpy(command,
            return_value(my_str_to_word_array(args2[i], "$"), my_shell));
            continue;
        }
        command = malloc(sizeof(char) * strlen(args2[i]) + 1);
        strcpy(command, args2[i]);
    }
    strcpy(args[1], command);
    free(command);
    free(args2);
    return args;
}
