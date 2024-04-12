/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Functions related to file handling
*/

#include <fcntl.h>
#include "shell.h"

int get_file_size(char const *filename)
{
    int fd = open(filename, S_IRUSR);
    unsigned int size = 0;
    int char_read = 0;
    char buffer[BUFSIZ];

    if (fd == SYS_ERROR)
        return OPEN_ERROR;
    do {
        size += char_read;
        char_read = read(fd, buffer, BUFSIZ - 1);
    } while (char_read != -1 && char_read != 0);
    close(fd);
    return size;
}

int open_append(char const *filename)
{
    int fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0644);
    char *err_msg = my_strcat("Open file error with ", filename);

    if (fd == SYS_ERROR) {
        perror(err_msg);
        free(err_msg);
        return ERROR;
    }
    free(err_msg);
    return fd;
}

int read_open(char const *filename)
{
    int fd = open(filename, O_RDONLY);
    char *err_msg = my_strcat("Open file error with ", filename);

    if (fd == SYS_ERROR) {
        perror(err_msg);
        free(err_msg);
        return ERROR;
    }
    free(err_msg);
    return ERROR;
}
