/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Functions related to get the last commands written in the shell
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

static int get_line_nb(char **lines)
{
    char *line = NULL;
    int nb = 0;

    if (lines == NULL)
        return -1;
    line = lines[my_strstrlen(lines) - 1];
    nb = my_special_getnbr(line);
    if (nb == 0 && line[0] != '0') {
        free_str_array(lines);
        return -1;
    }
    free_str_array(lines);
    return nb;
}

static int get_previous_cmd_num(void)
{
    int fd = read_open(HISTORIC_FILENAME);
    char *buffer = NULL;
    int chars_read = 0;

    if (fd == OPEN_ERROR && get_file_size(HISTORIC_FILENAME) > 0)
        return fd;
    if (get_file_size(HISTORIC_FILENAME) <= 0)
        return 0;
    buffer = malloc(sizeof(char) * get_file_size(HISTORIC_FILENAME) + 1);
    chars_read = read(fd, buffer, get_file_size(HISTORIC_FILENAME) - 1);
    close(fd);
    if (chars_read == SYS_ERROR) {
        perror("Reading last command number");
        return SYS_ERROR;
    }
    buffer[chars_read] = '\0';
    return get_line_nb(my_pimp_str_to_wa(buffer, "\n"));
}

static char *line_nb_format(int prev_num)
{
    char *nb = my_nb_to_str(prev_num);
    char *new_str = NULL;
    int index = 0;

    if (my_strlen(nb) >= HISTORY_NB_SIZE)
        return nb;
    new_str = malloc(sizeof(char) * (HISTORY_NB_SIZE + 1));
    if (new_str == NULL) {
        perror("line_nb_format malloc");
        return NULL;
    }
    for (int i = HISTORY_NB_SIZE - 1; i >= 0; i--) {
        if (index < my_strlen(nb))
            new_str[i] = nb[my_strlen(nb) - 1 - index];
        else
            new_str[i] = ' ';
        index++;
    }
    new_str[HISTORY_NB_SIZE] = '\0';
    return new_str;
}

static char *format_line(char const *cmd, int prev_num)
{
    char *num = line_nb_format(prev_num);
    char *num_space = my_strcat(num, " ");
    char *time = get_current_time();
    char *num_time = my_strcat(num_space, time);
    char *time_space = my_strcat(num_time, " ");
    char *tmp_msg = my_strcat(time_space, cmd);
    char *msg = my_strcat(tmp_msg, "\n");

    free(num);
    free(num_space);
    free(time);
    free(num_time);
    free(time_space);
    free(tmp_msg);
    return msg;
}

int add_command_to_save(char const *cmd)
{
    int fd = open_append(HISTORIC_FILENAME);
    int prev_num = get_previous_cmd_num();
    char *line = NULL;

    if (fd == ERROR || prev_num < 0)
        return ERROR;
    line = format_line(cmd, prev_num + 1);
    if (write(fd, line, my_strlen(line)) == SYS_ERROR) {
        perror("Write to save file");
        return ERROR;
    }
    close(fd);
    return SUCCESS;
}

static char **return_read_error(int fd)
{
    perror("Read error");
    close(fd);
    return NULL;
}

static char **add_command_to_end(char *buffer, char *cmd)
{
    char **file_by_line = NULL;
    char **final_array = NULL;

    file_by_line = my_pimp_str_to_wa(buffer, "\n");
    free(buffer);
    if (file_by_line == NULL)
        return NULL;
    final_array = malloc(sizeof(char *) * (my_strstrlen(file_by_line) + 2));
    if (final_array == NULL) {
        free_str_array(file_by_line);
        perror("add command to end malloc");
        return NULL;
    }
    final_array = my_strstrcpy(final_array, file_by_line);
    final_array[my_strstrlen(file_by_line)] = my_strdup(cmd);
    final_array[my_strstrlen(file_by_line) + 1] = NULL;
    free_str_array(file_by_line);
    return final_array;
}

char **get_array_from_prev_cmd(char *current_cmd)
{
    int fd = read_open(HISTORIC_FILENAME);
    char *buffer = NULL;
    int file_size = get_file_size(HISTORIC_FILENAME);
    int chars_read = 0;

    if (fd == ERROR || file_size <= 0)
        return NULL;
    buffer = malloc(sizeof(char) * (file_size + 1));
    if (buffer == NULL) {
        close(fd);
        perror("get array from prev command malloc");
        return NULL;
    }
    chars_read = read(fd, buffer, file_size - 1);
    if (chars_read == SYS_ERROR)
        return return_read_error(fd);
    close(fd);
    buffer[chars_read] = '\0';
    return add_command_to_end(buffer, current_cmd);
}

void display_historic(char **args, shell_info_t *my_shell)
{
    char *buffer = NULL;

    (void)args;
    buffer = get_file_content(HISTORIC_FILENAME);
    if (buffer == NULL || my_strlen(buffer) <= 0) {
        my_shell->exit_status = ERROR;
        return;
    }
    my_putstr(buffer);
    free(buffer);
    my_shell->exit_status = SUCCESS;
}
