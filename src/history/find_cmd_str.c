/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Functions to find command with string
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"

static bool check_arg(char *arg, char const *to_find)
{
    for (unsigned int i = 0; arg[i]; i++) {
        if (strncmp(arg + i, to_find, strlen(to_find)) == 0) {
            return true;
        }
    }
    return false;
}

static bool check_line(char **str, char const *to_find)
{
    if (str == NULL) {
        return false;
    }
    for (unsigned int i = 0; str[i]; i++) {
        if (check_arg(str[i], to_find)) {
            return true;
        }
    }
    return false;
}

static int try_cmd_contain(char **buf, char const *str)
{
    char **to_test = NULL;

    for (int line = my_strstrlen(buf) - 1; line >= 0; line--) {
        to_test = my_pimp_str_to_wa(buf[line], " ");
        if (check_line(to_test + 2, str)) {
            return line;
        }
    }
    return -1;
}

static char *display_last_search(char *str)
{
    if (str == NULL) {
        dprintf(2, "No prev search.\n");
        return NULL;
    }
    return str;
}

static char *get_last_cmd(char **lines, int nb, char const *str)
{
    char *cmd = NULL;

    if (nb < 0) {
        free_str_array(lines);
        return not_found_error(str);
    }
    cmd = find_cmd_in_line(lines[nb]);
    remove_from_file(lines, (unsigned int)nb);
    free_str_array(lines);
    return cmd;
}

static char *cmd_contains(char *str)
{
    static char *last_search = NULL;
    char *buffer = NULL;
    char **lines = NULL;

    if (str == NULL) {
        return display_last_search(str);
    }
    buffer = get_file_content(HISTORIC_FILENAME);
    if (buffer == NULL) {
        return NULL;
    }
    lines = my_pimp_str_to_wa(buffer, "\n");
    free(buffer);
    if (lines == NULL) {
        return NULL;
    }
    last_search = get_last_cmd(lines, try_cmd_contain(lines, str), str);
    return last_search;
}

static char *find_matching_start(char **lines, char const *str)
{
    char **to_test = NULL;
    int i = my_strstrlen(lines) - 1;

    while (i >= 0) {
        to_test = my_pimp_str_to_wa(lines[i], " ");
        if (strncmp(to_test[2], str, strlen(str)) == 0) {
            free_str_array(to_test);
            return get_last_cmd(lines, i, str);
        }
        i--;
        free_str_array(to_test);
    }
    return get_last_cmd(lines, i, str);
}

static char *cmd_start(char const *str)
{
    char *buffer = get_file_content(HISTORIC_FILENAME);
    char **lines = NULL;

    if (buffer == NULL) {
        return NULL;
    }
    lines = my_pimp_str_to_wa(buffer, "\n");
    if (lines == NULL) {
        free(buffer);
        return NULL;
    }
    free(buffer);
    return find_matching_start(lines, str);
}

char *get_cmd_with_str(char *str)
{
    if (str[0] == '?') {
        return cmd_contains(str + 1);
    }
    return cmd_start(str);
}
