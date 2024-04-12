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

char **get_array_from_prev_cmd(char *current_cmd)
{
    int fd = read_open(HISTORIC_FILENAME);
    char *buffer = NULL;
    int file_size = get_file_size(HISTORIC_FILENAME);

    if (fd == ERROR || file_size == OPEN_ERROR)
        return ERROR;
    read(fd, &buffer, file_size);
}
