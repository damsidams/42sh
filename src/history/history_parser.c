/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** File to start good history functions
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

static char *get_cmd_from_hist(char *args)
{
    if (args == NULL) {
        return NULL;
    }
    if (args[0] == HISTORY_CHAR) {
        return find_last_cmd();
    }
    if (atoi(args) == 0 && args[0] != '0') {
        return get_cmd_with_str(args);
    }
    return get_the_n_cmd(args);
}

static char *remove_historic(char *str)
{
    char *new_str = calloc(strlen(str), sizeof(char));
    unsigned int index = 0;

    if (new_str == NULL) {
        perror("remove_backtick calloc failed");
        return NULL;
    }
    for (unsigned int i = 1; str[i]; i++) {
        new_str[i - 1] = str[i];
        index = i;
    }
    new_str[index] = '\0';
    free(str);
    return new_str;
}

static char *get_good_string(char *cmd,
    int first_char, int next_space)
{
    char *to_replace = strndup(cmd + first_char, next_space);
    char *new_str = NULL;

    to_replace[next_space] = '\0';
    to_replace = remove_historic(to_replace);
    to_replace = get_cmd_from_hist(to_replace);
    if (to_replace == NULL) {
        return NULL;
    }
    new_str = calloc(strlen(cmd) - next_space + strlen(to_replace) + 1,
        sizeof(char));
    if (new_str == NULL) {
        perror("history_parser.c: get good string calloc failed");
        return NULL;
    }
    new_str = strncpy(new_str, cmd, first_char);
    new_str = strcat(new_str, to_replace);
    new_str = strcat(new_str, cmd + first_char + next_space);
    free(to_replace);
    return new_str;
}

static bool history_sign(char const *str)
{
    if (str == NULL) {
        return false;
    }
    for (unsigned int i = 0; str[i]; i++) {
        if (str[i] == HISTORY_CHAR) {
            return true;
        }
    }
    return false;
}

static int space_str(char const *str)
{
    if (str == NULL) {
        return HISTORIC_ERROR;
    }
    for (unsigned int i = 1; str[i]; i++) {
        if (str[i] == ' ') {
            return i;
        }
    }
    return strlen(str);
}

static char *parse_cmd(char *cmd, bool *change)
{
    int next_space = 0;

    for (unsigned int i = 0; cmd[i]; i++) {
        if (cmd[i] == HISTORY_CHAR) {
            next_space = space_str(cmd + i);
            *change = true;
        }
        if (next_space != 0) {
            cmd = get_good_string(cmd, i, next_space);
        }
        if (cmd == NULL) {
            return NULL;
        }
        next_space = 0;
    }
    return cmd;
}

char *check_if_historic(char *cmd, shell_info_t *my_shell)
{
    bool change = false;

    if (!history_sign(cmd)) {
        return cmd;
    }
    cmd = parse_cmd(cmd, &change);
    if (cmd == NULL) {
        my_shell->exit_status = 1;
        return NULL;
    }
    my_shell->exit_status = 0;
    if (change) {
        printf("%s\n", cmd);
    }
    return cmd;
}
