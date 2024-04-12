/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Functions related to get the last commands written in the shell
*/

#include <stdio.h>
#include "shell.h"

static int open_command_file(void)
{
    int fd = open(HISTORIC_FILENAME, O_RDWR | O_APPEND | O_CREAT, 0644);

    if (fd == SYS_ERROR) {
        perror("Save file opening");
        return ERROR;
    }
    return fd;
}

int add_command_to_save(char const *cmd)
{
    int fd = open_command_file();

    if (fd == ERROR)
        return ERROR;
    if (write(fd, cmd, my_strlen(cmd)) == SYS_ERROR) {
        perror("Write to save file");
        return ERROR;
    }
    close(fd);
    return SUCCESS;
}
