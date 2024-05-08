/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
** File description:
** insert_var.c
*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

static char **get_from_env(char **env, char *element)
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

static char **get_from_local(local_t *local, char *element)
{
    local_t *temp = local;
    char **command = malloc(sizeof(char *) * 3);

    if (!command) {
        return NULL;
    }
    for (int i = 0; i != 3; i++) {
        command[i] = NULL;
    }
    while (temp) {
        if (strcmp(temp->name, element) == 0) {
            command[0] = strdup(temp->name);
            command[1] = strdup(temp->value);
        }
        temp = temp->next;
    }
    return command;
}

static char *return_value(char **args, shell_info_t *my_shell)
{
    char **element = get_from_env(my_shell->env, args[0]);

    if (!element) {
        element = get_from_local(my_shell->local, args[0]);
        if (!element) {
            printf("%s: Undefined variable.", args[0]);
            return NULL;
        }
    }
    return element[1];
}

char **check_dollar(char **args, shell_info_t *my_shell)
{
    char *command = NULL;
    char **temp = NULL;

    for (int i = 0; args[i] != NULL; i++) {
        if (strncmp(args[i], "$", 1) == 0) {
            temp = my_str_to_word_array(args[i], "$");
            command = strdup(return_value(temp, my_shell));
            free_str_array(temp);
            continue;
        }
        command = strdup(args[i]);
    }
    free(args[1]);
    args[1] = strdup(command);
    return args;
}
