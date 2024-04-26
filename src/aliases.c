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

static alias_t *add_alias(char *args, alias_t *list_alias)
{
    alias_t *alias = malloc(sizeof(alias_t));
    char **alias_command = my_str_to_word_array(args, "=");
    char **real_command = NULL;

    if (alias == NULL || alias_command[1] == NULL)
        return NULL;
    real_command = my_str_to_word_array(alias_command[1], "'");
    alias->alias_cmd = my_strdup(alias_command[0]);
    alias->real_cmd = my_strdup(real_command[0]);
    alias->next = list_alias;
    return alias;
}

static char **set_alias(void)
{
    char **set_alias = malloc(sizeof(char *) * 14);

    if (set_alias == NULL)
        return NULL;
    set_alias[0] = my_strdup("egrep='egrep --color=auto'");
    set_alias[1] = my_strdup("fgrep='fgrep --color=auto'");
    set_alias[2] = my_strdup("grep='grep --color=auto'");
    set_alias[3] = my_strdup("l.='ls -d .* --color=auto'");
    set_alias[4] = my_strdup("ll='ls -l --color=auto'");
    set_alias[5] = my_strdup("ls='ls --color=auto'");
    set_alias[6] = my_strdup("which='(alias; declare -f) | /usr/bin/which --tty-only --read-alias --read-functions --show-tilde --show-dot'");
    set_alias[7] = my_strdup("xzegrep='xzegrep --color=auto'");
    set_alias[8] = my_strdup("xzfgrep='xzfgrep --color=auto'");
    set_alias[9] = my_strdup("xzgrep='xzgrep --color=auto'");
    set_alias[10] = my_strdup("zegrep='zegrep --color=auto'");
    set_alias[11] = my_strdup("zfgrep='zfgrep --color=auto'");
    set_alias[12] = my_strdup("zgrep='zgrep --color=auto'");
    set_alias[13] = NULL;
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

    for (int i = 0; i != 13; i++) {
        init_alias = add_alias(set_command[i], init_alias);
    }
    return init_alias;
}

void my_alias(char **args, shell_info_t *my_shell)
{
    char *alias_command = NULL;

    if (args[1] == NULL) {
        display_list_alias(my_shell);
        return;
    }
    alias_command = malloc(sizeof(char) * my_strlen(args[1]) + 1);
    if (alias_command == NULL)
        return;
    my_strcpy(alias_command, args[1]);
    if (args[1] != NULL) {
        my_shell->list_alias = add_alias(alias_command, my_shell->list_alias);
        return;
    }
    my_shell->exit_status = 0;
}
