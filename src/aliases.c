/*
** EPITECH PROJECT, 2024
** lisagoulmot
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
#include <string.h>

static alias_t *add_alias(char *alias_command, char *real_command,
    alias_t *list_alias)
{
    alias_t *alias = malloc(sizeof(alias_t));

    if (alias == NULL || alias_command == NULL || real_command == NULL)
        return NULL;
    alias->alias_cmd = my_strdup(alias_command);
    alias->real_cmd = my_strdup(real_command);
    alias->next = list_alias;
    return alias;
}

static void display_list_alias(shell_info_t *my_shell)
{
    alias_t *current = NULL;

    if (my_shell->list_alias == NULL)
        return;
    current = my_shell->list_alias;
    while (current != NULL && current->real_cmd != NULL) {
        printf("%s\t%s\n", current->alias_cmd, current->real_cmd);
        current = current->next;
    }
}

static char *set_buffer(char *buffer, int fd, alias_t *current)
{
    int lengh = 0;

    lengh = strlen(current->alias_cmd) * strlen(current->real_cmd) + 10;
    buffer = malloc(sizeof(char) * lengh);
    strcpy(buffer, current->alias_cmd);
    strcat(buffer, " ");
    strcat(buffer, current->real_cmd);
    strcat(buffer, "\n");
    write(fd, buffer, strlen(buffer));
    return buffer;
}

static int create_42rc(shell_info_t *my_shell)
{
    int fd = open("42rc", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    alias_t *current = my_shell->list_alias;
    char *buffer = NULL;

    if (fd == -1)
        return ERROR;
    if (my_shell->list_alias == NULL)
        return ERROR;
    while (current) {
        buffer = set_buffer(buffer, fd, current);
        current = current->next;
        free(buffer);
    }
    close(fd);
    return SUCCESS;
}

int exec_alias(shell_info_t *my_shell, char *args)
{
    alias_t *current = my_shell->list_alias;

    while (current) {
        if (alias_loop(args, my_shell) == 1)
            return 1;
        if (my_strcmp(current->alias_cmd, args) == 0) {
            exec_alias_loop(my_shell, current);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void my_alias(char **args, shell_info_t *my_shell)
{
    create_42rc(my_shell);
    if (args[1] == NULL) {
        display_list_alias(my_shell);
        return;
    }
    if (args[1] != NULL) {
        my_shell->list_alias = add_alias(args[1], args[2],
            my_shell->list_alias);
        create_42rc(my_shell);
        return;
    }
    my_shell->exit_status = 0;
}

void del_alias(char **args, shell_info_t *my_shell)
{
    alias_t *current = my_shell->list_alias;
    alias_t *prev_node = my_shell->list_alias;

    if (args[1] == NULL)
        return;
    if (current != NULL && strcmp(current->alias_cmd, args[1]) == 0) {
        my_shell->list_alias = current->next;
        free(current);
        return;
    }
    while (current != NULL && strcmp(current->alias_cmd, args[1]) != 0) {
        prev_node = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    prev_node->next = current->next;
    free(current);
}
