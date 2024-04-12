/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Functions related to get the last commands written in the shell
*/

#include <fcntl.h>
#include <stdio.h>
#include "shell.h"

int add_command_to_save(char const *cmd)
{
    int fd = open_command_file(HISTORIC_FILENAME);

    if (fd == ERROR)
        return ERROR;
    if (write(fd, cmd, my_strlen(cmd)) == SYS_ERROR) {
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
        free_strarray(file_by_line);
        perror("add command to end malloc");
        return NULL;
    }
    final_array = my_strstrcpy(final_array, file_by_line);
    final_array[my_strstrlen(file_by_line)] = my_strdup(cmd);
    final_array[my_strstrlen(file_by_line) + 1] = NULL;
    fre_strarray(file_by_line);
    return final_array;
}

char **get_array_from_prev_cmd(char *current_cmd)
{
    int fd = read_open(HISTORIC_FILENAME);
    char *buffer = NULL;
    int file_size = get_file_size(HISTORIC_FILENAME);
    int chars_read = 0;

    if (fd == ERROR || file_size <= 0)
        return ERROR;
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
