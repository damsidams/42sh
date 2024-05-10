/*
** EPITECH PROJECT, 2024
** lisagoulmot
** File description:
** alias loop
*/
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"

static int command_loop_check(char *args, shell_info_t *my_shell)
{
    alias_t *current = my_shell->list_alias;
    alias_t *current2 = my_shell->list_alias;

    while (current) {
        if (strcmp(current->alias_cmd, args) == 0) {
            break;
        }
        current = current->next;
    }
    while (current2) {
        if (strcmp(current->real_cmd, current2->alias_cmd) == 0) {
            return 1;
        }
        current2 = current2->next;
    }
    return 0;
}

int alias_loop_check(shell_info_t *my_shell, char *args)
{
    alias_t *current = my_shell->list_alias;

    while (current) {
        if (strcmp(current->alias_cmd, args) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

alias_t *change_alias_cmd(char **args, shell_info_t *my_shell)
{
    while (my_shell->list_alias) {
        if (strcmp(my_shell->list_alias->alias_cmd, args[1]) == 0) {
            my_shell->list_alias->real_cmd = args[2];
            return my_shell->list_alias;
        }
        my_shell->list_alias = my_shell->list_alias->next;
    }
    return my_shell->list_alias;
}

int alias_loop(char *args, shell_info_t *my_shell)
{
    alias_t *current = my_shell->list_alias;

    while (current) {
        if (strcmp(current->real_cmd, args) == 0
            && command_loop_check(args, my_shell) == 1) {
            printf("Alias loop.\n");
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int exec_alias_loop(shell_info_t *my_shell, alias_t *list)
{
    alias_t *current = my_shell->list_alias;
    char **cmd = NULL;

    while (current) {
        if (alias_loop_check(my_shell, list->real_cmd) == 1 &&
            strcmp(list->real_cmd, current->alias_cmd) == 0) {
            cmd = my_str_to_word_array(current->real_cmd, " ");
            exec_cmd(cmd, my_shell);
            return 1;
        }
        current = current->next;
    }
    cmd = my_str_to_word_array(list->real_cmd, " ");
    exec_cmd(cmd, my_shell);
    free_str_array(cmd);
    return 0;
}
