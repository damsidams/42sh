/*
** EPITECH PROJECT, 2024
** aliases
** File description:
** aliases
*/
#include "my.h"
#include "struct.h"
#include "shell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static list_t *add_alias(char *args, list_t *list_alias)
{
    alias_t *alias = malloc(sizeof(alias_t));
    char **alias_command = my_str_to_word_array(args, "=");
    char **real_command = NULL;

    if (alias == NULL || alias_command[1] == NULL)
        return;
    real_command = my_str_to_word_array(alias_command[1], "'");
    alias->alias_cmd = my_strdup(alias_command[0]);
    alias->real_cmd = my_strdup(real_command[0]);
    alias->next = list_alias->premier;
    list_alias->premier = alias;
    return list_alias;
}

static list_t *init_list(void)
{
    list_t *list_alias = malloc(sizeof(list_t));
    alias_t *alias = malloc(sizeof(alias_t));

    if (list_alias == NULL || alias == NULL)
        return;
    alias->alias_cmd = NULL;
    alias->real_cmd = NULL;
    alias->next = NULL;
    list_alias->premier = alias;
    return list_alias;
}

void my_alias(char **args, shell_info_t *my_shell)
{
    list_t *list_alias = init_list();
    char *alias_command = malloc(sizeof(char) * my_strlen(args[1]) + 1);

    if (alias_command == NULL)
        return;
    my_strcpy(alias_command, args[1]);
    if (args[1] != NULL) {
        list_alias = add_alias(alias_command, list_alias);
    }
    my_shell->exit_status = 0;
}
