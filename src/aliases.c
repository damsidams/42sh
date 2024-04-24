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

static void display_list_alias(list_t *list_alias)
{
    alias_t *current = NULL;

    if (list_alias == NULL)
        return;
    current = list_alias->premier;
    while (current != NULL && current->real_cmd != NULL) {
        printf("alias '%s'\n", current->real_cmd);
        current = current->next;
    }
}

void exec_alias(list_t *list_alias, shell_info_t *my_shell, char *args)
{
    char **new_command = my_str_to_word_array(args, "=");
    char **real_command = my_str_to_word_array(new_command[1], "'");
    alias_t *current = list_alias->premier;

    while (current) {
        if (my_strcmp(current->alias_cmd, new_command[0])) {
            command_handling(my_shell, real_command);
            return;
        }
        current = current->next;
    }
}

static char **set_alias(void)
{
    char **set_alias = malloc(sizeof(char *) * 14);

    if (set_alias == NULL)
        return;
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

void my_alias(char **args, shell_info_t *my_shell)
{
    list_t *list_alias = init_list();
    char *alias_command = malloc(sizeof(char) * my_strlen(args[1]) + 1);
    char **set_commands = set_alias();

    if (alias_command == NULL)
        return;
    for (int i = 0; i != 13; i++) {
        add_alias(set_commands[i], list_alias);
    }
    if (args[1] == NULL) {
        display_list_alias(list_alias);
        return;
    }
    my_strcpy(alias_command, args[1]);
    if (args[1] != NULL) {
        list_alias = add_alias(alias_command, list_alias);
        return;
    }
    exec_alias(list_alias, my_shell, alias_command);
    my_shell->exit_status = 0;
}
