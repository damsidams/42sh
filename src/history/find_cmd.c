/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Find the command in history
*/

#include "shell.h"

static char *find_cmd_in_line(char *line)
{
    char **args = my_pimp_str_to_wa(line, " ");
    char *cmd = strdup(args[2]);

    free_str_array(args);
    return cmd;
}

static char *find_cmd_by_event(char **lines, int cmd_nb)
{
    char *cmd = NULL;

    for (unsigned int i = 0; lines[i]; i++) {
	if (atoi(lines[i][0]) == cmd_nb) {
	    cmd = strdup(lines[i][2]);
	    free_str_array(lines);
	    return cmd;
	}
    }
    dprintf(2, "%d: Event not found.\n", cmd_nb);
    return NULL;
}

static char *not_found_error(char const *cmd_nb)
{
    dprintf(2, "%s: Event not found.\n", cmd_nb);
    return NULL;
}

static char *get_n_previous_cmd(char **lines, int cmd_nb)
{
    if (my_strstrlen(lines) < cmd_nb * -1) {
	return not_found_error(cmd_nb);
    }
    cmd = find_cmd_in_line(lines[my_strstrlen(lines) + cmd_nb]);
    free_str_array(lines);
    return cmd;
}

static bool is_zero(char *cmd)
{
    if (cmd == NULL) {
	return false;
    }
    for (unsigned int i = 0; cmd[i]; i++) {
	if (cmd[i] != '0') {
	    return false;
	}
    }
    return true;
}

char *get_the_n_cmd(char *history_arg)
{
    char *buffer = get_file_content(HISTORIC_FILENAME);
    char **lines = NULL;
    char *cmd = NULL;
    int cmd_nb = atoi(history_arg + 1);

    if (buffer == NULL || (cmd_nb == 0 && !is_zero(history_arg + 1))) {
	return not_found_error(history_arg + 1);
    }
    lines = my_pimp_str_to_wa(buffer, "\n");
    if (cmd_nb < 0) {
	return get_n_previous_cmd(lines, cmd_nb);
    }
    return find_cmd_by_event(lines, cmd_nb);
}

char *find_last_cmd(void)
{
    char *buffer = get_file_content(HISTORIC_FILENAME);
    char **lines = NULL;
    char *cmd = NULL;

    if (buffer == NULL) {
	return not_found_error("!!");
    }
    lines = my_pimp_str_to_wa(buffer, "\n");
    cmd = strdup(lines[my_strstrlen(lines) - 1]);
    free_str_array(lines);
    return cmd;
}
