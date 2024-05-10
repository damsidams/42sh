/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
** File description:
** unset.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "struct.h"

static local_t *del_var(char *var, local_t *local)
{
    local_t *temp = local;

    if (temp && strcmp(var, temp->name) == 0) {
        local = local->next;
        return local;
    }
    while (temp && temp->next) {
        if (strcmp(var, temp->next->name) == 0) {
            free(temp->next->name);
            free(temp->next->value);
            temp->next = temp->next->next;
            return local;
        }
        temp = temp->next;
    }
    return local;
}

void unset_local(char **args, shell_info_t *my_shell)
{
    if (my_strstrlen(args) == 1) {
        printf("unset: Too few arguments.\n");
        my_shell->exit_status = 1;
    }
    for (int i = 1; args[i]; i++) {
        my_shell->local = del_var(args[i], my_shell->local);
    }
    my_shell->exit_status = SUCCESS;
}
