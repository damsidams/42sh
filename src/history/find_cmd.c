/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Find the command in history
*/

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

void remove_from_file(char **file_content, unsigned int line_nb)
{
    FILE *file = fopen(HISTORIC_FILENAME, "w");
    unsigned int i = 0;

    while (file_content[i]) {
        if (i != line_nb) {
            fprintf(file, "%s\n", file_content[i]);
        }
        i++;
    }
    fclose(file);
}

static unsigned int get_full_len(char **args)
{
    unsigned int size = 0;

    if (args == NULL) {
        return 0;
    }
    for (unsigned int i = 0; args[i]; i++) {
        size += strlen(args[i]);
    }
    return size + my_strstrlen(args) - 1;
}

static char *create_str_from_strstr(char **args)
{
    unsigned int len = get_full_len(args);
    char *cmd = calloc(len + 1, sizeof(char));

    cmd = strcpy(cmd, args[0]);
    for (unsigned int i = 1; args[i]; i++) {
        strcat(cmd, " ");
        strcat(cmd, args[i]);
    }
    return cmd;
}

char *find_cmd_in_line(char *line)
{
    char **args = my_pimp_str_to_wa(line, " ");
    char *cmd = create_str_from_strstr(args + 2);

    free_str_array(args);
    return cmd;
}

static char *find_cmd_by_event(char **lines, int cmd_nb)
{
    char *cmd = NULL;
    char **args = NULL;

    for (unsigned int i = 0; lines[i]; i++) {
        args = my_pimp_str_to_wa(lines[i], " \n");
        if (atoi(args[0]) == cmd_nb) {
            cmd = create_str_from_strstr(args + 2);
            free_str_array(args);
            remove_from_file(lines, i);
            return cmd;
        }
        free_str_array(args);
    }
    dprintf(2, "%d: Event not found.\n", cmd_nb);
    return NULL;
}

char *not_found_error(char const *cmd_nb)
{
    dprintf(2, "%s: Event not found.\n", cmd_nb);
    return NULL;
}

static char *get_n_previous_cmd(char **lines, int cmd_nb, char const *hist)
{
    char *cmd = NULL;

    if (my_strstrlen(lines) < cmd_nb * -1) {
        return not_found_error(hist);
    }
    cmd = find_cmd_in_line(lines[my_strstrlen(lines) + cmd_nb]);
    remove_from_file(lines, my_strstrlen(lines) + cmd_nb);
    free_str_array(lines);
    return cmd;
}

char *get_the_n_cmd(char *history_arg)
{
    char *buffer = get_file_content(HISTORIC_FILENAME);
    char **lines = NULL;
    int cmd_nb = atoi(history_arg);

    if (buffer == NULL || cmd_nb == 0) {
        return not_found_error(history_arg + 1);
    }
    lines = my_pimp_str_to_wa(buffer, "\n");
    if (cmd_nb < 0) {
        return get_n_previous_cmd(lines, cmd_nb, history_arg);
    }
    return find_cmd_by_event(lines, cmd_nb);
}

char *find_last_cmd(void)
{
    char *buffer = get_file_content(HISTORIC_FILENAME);
    char **lines = NULL;
    char **line = NULL;
    char *cmd = NULL;

    if (buffer == NULL) {
        return not_found_error("!!");
    }
    lines = my_pimp_str_to_wa(buffer, "\n");
    line = my_pimp_str_to_wa(lines[my_strstrlen(lines) - 1], " ");
    cmd = create_str_from_strstr(line + 2);
    remove_from_file(lines, my_strstrlen(lines) - 1);
    free_str_array(lines);
    free_str_array(line);
    return cmd;
}
