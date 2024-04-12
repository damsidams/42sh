/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Functions related to file handling
*/

#include "shell.h"


int open_append(char const *filename)
{
    int fd = open(HISTORIC_FILENAME, O_RDWR | O_APPEND | O_CREAT, 0644);
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
    int fd = open(HISTORIC_FILENAME, O_RDONLY);
    char *err_msg = my_strcat("Open file error with ", filename);

    if (fd == SYS_ERROR) {
        perror(err_msg);
        free(err_msg);
        return ERROR;
    }
    free(err_msg);
    return ERROR;

}
