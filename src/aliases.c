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

static char **set_alias(void)
{
    char **set_alias = malloc(sizeof(char *) * 13);

    if (set_alias == NULL)
        return NULL;
    set_alias[0] = my_strdup("egrep=egrep --color=auto");
    set_alias[1] = my_strdup("fgrep=fgrep --color=auto");
    set_alias[2] = my_strdup("grep=grep --color=auto");
    set_alias[3] = my_strdup("l.=ls -d .* --color=auto");
    set_alias[4] = my_strdup("ll=ls -l --color=auto");
    set_alias[5] = my_strdup("ls=ls --color=auto");
    set_alias[6] = my_strdup("xzegrep=xzegrep --color=auto");
    set_alias[7] = my_strdup("xzfgrep=xzfgrep --color=auto");
    set_alias[8] = my_strdup("xzgrep=xzgrep --color=auto");
    set_alias[9] = my_strdup("zegrep=zegrep --color=auto");
    set_alias[10] = my_strdup("zfgrep=zfgrep --color=auto");
    set_alias[11] = my_strdup("zgrep=zgrep --color=auto");
    set_alias[12] = NULL;
    return set_alias;
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

int exec_alias(shell_info_t *my_shell, char *args)
{
    alias_t *current = my_shell->list_alias;
    char **cmd = NULL;

    while (current) {
        if (my_strcmp(current->alias_cmd, args) == 0) {
            cmd = my_str_to_word_array(current->real_cmd, " ");
            exec_cmd(cmd, my_shell);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

alias_t *init_alias(void)
{
    alias_t *init_alias = NULL;
    char **set_command = set_alias();
    char **args = NULL;

    for (int i = 0; i != 12; i++) {
        args = my_str_to_word_array(set_command[i], "=");
        init_alias = add_alias(args[0], args[1], init_alias);
        free_str_array(args);
    }
    for (int i = 0; set_command[i]; i++) {
        free(set_command[i]);
    }
    free(set_command);
    return init_alias;
}

char *set_buffer(char *buffer, int fd, alias_t *current)
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

int create_42rc(shell_info_t *my_shell)
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
