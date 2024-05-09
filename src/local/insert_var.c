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

static char *get_from_env(char **env, char *element)
{
    char **line = NULL;
    char *value = NULL;

    for (int i = 0; env[i]; i++) {
        line = my_str_to_word_array(env[i], "=");
        if (strcmp(line[0], element) == 0) {
            value = strdup(line[1]);
            free_str_array(line);
            return value;
        }
        free_str_array(line);
        line = NULL;
    }
    return NULL;
}

static char *get_from_local(local_t *local, char *element)
{
    local_t *temp = local;
    char *command = NULL;

    while (temp) {
        if (strcmp(temp->name, element) == 0) {
            command = strdup(temp->value);
            break;
        }
        temp = temp->next;
    }
    return command;
}

static char *return_value(char *args, shell_info_t *my_shell)
{
    char *element = get_from_env(my_shell->env, args);

    if (!element) {
        element = get_from_local(my_shell->local, args);
        if (!element) {
            printf("%s: Undefined variable.\n", args);
            my_shell->exit_status = 1;
            return NULL;
        }
    }
    return element;
}

static int get_len(char *arg, int index)
{
    int len = 0;

    for (int i = index; (arg[i] > 65 || arg[i] < 91) &&
        ((arg[i] > 97 || arg[i] < 122)) && arg[i] != '\0'; i++) {
        len++;
    }
    return len;
}

static char *cat_new_var(char *var, char *arg, int index, int var_len)
{
    char *final = NULL;
    char *arg_cpy = strdup(arg);
    char *var_ptr = var;

    if (!var) {
        free(arg_cpy);
        return NULL;
    }
    for (int i = 0; i != index + var_len; i++) {
        arg_cpy++;
    }
    if (arg[0] != '$') {
        final = strndup(arg, index - 1);
        var = my_strcat(final, var);
        var_ptr = var;
    }
    if (arg_cpy[0] == '\0') {
        free(final);
        return var;
    }
    var = my_strcat(var, arg_cpy);
    free(var_ptr);
    free(final);
    return var;
}

static char *replace_dollar(char *arg, int index, shell_info_t *my_shell)
{
    int size = 0;
    int var_len = get_len(arg, index);
    char *var = malloc(sizeof(char) * var_len + 1);
    char *var_ptr = var;

    for (int i = index; my_char_is_alpha(arg[i]) && arg[i] != '\0'; i++) {
        var[size] = arg[i];
        size++;
    }
    var[size] = '\0';
    var_len = my_strlen(var);
    var = return_value(var, my_shell);
    free(var_ptr);
    return cat_new_var(var, arg, index, var_len);
}

char *parse_arg(char *arg, shell_info_t *my_shell)
{
    for (int i = 0; arg && arg[i] != '\0'; i++) {
        if ((i == 0 && arg[i] == '$') || (i > 0 && arg[i] == '$'
            && arg[i - 1] != '\\')) {
            arg = replace_dollar(arg, i + 1, my_shell);
            i = 0;
        }
    }
    return arg;
}

char **replace_var(char **args, shell_info_t *my_shell)
{
    if (!args) {
        return args;
    }
    for (int i = 0; args[i]; i++) {
        if (my_char_in_str('$', args[i])) {
            args[i] = parse_arg(args[i], my_shell);
        }
        if (!args[i]) {
            free_str_array(args);
            return NULL;
        }
    }
    return args;
}
