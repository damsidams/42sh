/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
** File description:
** set.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell.h"
#include "struct.h"
#include "my.h"

static void print_list(local_t *local)
{
    local_t *temp = local;

    while (temp) {
        if (temp->value) {
            printf("%s\t%s\n", temp->name, temp->value);
        } else {
            printf("%s\n", temp->name);
        }
        temp = temp->next;
    }
}

static bool found_var(char **var, local_t *local)
{
    local_t *temp = local;

    while (temp) {
        if (strcmp(temp->name, var[0]) == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

static local_t *place_var(local_t *new_var, local_t *local)
{
    local_t *temp = local;

    while (temp && temp->next) {
        if (strcmp(new_var->name, temp->next->name) >= 0) {
            new_var->next = temp->next;
            temp->next = new_var;
            return local;
        }
        temp = temp->next;
    }
    new_var->next = local;
    return new_var;
}

static local_t *create_var(char **var, local_t *local)
{
    local_t *new_var = malloc(sizeof(local_t));

    if (!new_var) {
        return NULL;
    }
    new_var->name = strdup(var[0]);
    if (my_strstrlen(var) == 2) {
        new_var->value = strdup(var[1]);
    } else {
        new_var->value = NULL;
    }
    return place_var(new_var, local);
}

static local_t *set_existing_var(char **var, local_t *local)
{
    local_t *temp = local;

    print_str_array(var);
    while (temp) {
        if (strcmp(var[0], temp->name) == 0 && temp->name) {
            free(temp->value);
            temp->value = strdup(var[1]);
            return local;
        }
        if (strcmp(var[0], temp->name) == 0 && !temp->name) {
            temp->value = strdup(var[1]);
            return local;
        }
        temp = temp->next;
    }
    return local;
}

static void set_var(char *var, shell_info_t *my_shell)
{
    char **equal_sep = my_str_to_word_array(var, "=");

    if (!equal_sep) {
        return;
    }
    if (my_strstrlen(equal_sep) == 2) {
        if (!found_var(equal_sep, my_shell->local)) {
            my_shell->local = create_var(equal_sep, my_shell->local);
        } else {
            my_shell->local = set_existing_var(equal_sep, my_shell->local);
        }
    }
    if (my_strstrlen(equal_sep) == 1) {
        my_shell->local = create_var(equal_sep, my_shell->local);
    }
}

void set_local(char **args, shell_info_t *my_shell)
{
    if (my_strstrlen(args) == 1) {
        print_list(my_shell->local);
        my_shell->exit_status = SUCCESS;
        return;
    }
    for (int i = 1; args[i]; i++) {
        set_var(args[i], my_shell);
        my_shell->exit_status = SUCCESS;
    }
}
