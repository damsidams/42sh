/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Function related to backtick
*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"

static int backtick_str(char const *str)
{
    if (str == NULL) {
        return BACKTICK_ERROR;
    }
    for (unsigned int i = 1; str[i]; i++) {
        if (str[i] == BACKTICK) {
            return i + 1;
        }
    }
    return BACKTICK_ERROR;
}

static char *remove_backtick(char *str)
{
    char *new_str = calloc(strlen(str) - 1, sizeof(char));
    unsigned int index = 0;

    if (new_str == NULL) {
        perror("remove_backtick calloc failed");
        return NULL;
    }
    for (unsigned int i = 1; str[i + 1]; i++) {
        new_str[i - 1] = str[i];
        index = i;
    }
    new_str[index] = '\0';
    free(str);
    return new_str;
}

static char *get_good_string(shell_info_t *my_shell, char *cmd
    , int first_backtick, int next_backtick)
{
    char *to_replace = strndup(cmd + first_backtick, next_backtick);
    char *new_str = NULL;

    to_replace[next_backtick] = '\0';
    to_replace = remove_backtick(to_replace);
    to_replace = get_backtick_output(my_shell, to_replace);
    new_str = calloc(strlen(cmd) - next_backtick + strlen(to_replace) + 1,
        sizeof(char));
    if (new_str == NULL) {
        perror("backtick.c: get good string calloc failed");
        return NULL;
    }
    new_str = strncpy(new_str, cmd, first_backtick);
    new_str = strcat(new_str, to_replace);
    new_str = strcat(new_str, cmd + first_backtick + next_backtick);
    free(to_replace);
    return new_str;
}

static bool still_backtick(char *str)
{
    for (unsigned int i = 0; str[i]; i++) {
        if (str[i] == BACKTICK) {
            return true;
        }
    }
    return false;
}

static char *replace_backtick_str(char *cmd, shell_info_t *my_shell)
{
    int next_backtick = 0;

    for (unsigned int i = 0; cmd[i] && still_backtick(cmd); i++) {
        if (cmd[i] == BACKTICK) {
            next_backtick = backtick_str(cmd + i);
        }
        if (next_backtick == BACKTICK_ERROR) {
            return NULL;
        }
        if (next_backtick != 0) {
            cmd = get_good_string(my_shell, cmd, i, next_backtick);
        }
        next_backtick = 0;
    }
    return cmd;
}

char **replace_backtick(char **cmd, shell_info_t *my_shell)
{
    for (unsigned int i = 0; cmd[i]; i++) {
        cmd[i] = replace_backtick_str(cmd[i], my_shell);
    }
    return cmd;
}
