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
#include "shell.h"

bool is_backtick(char const *str)
{
    if (str == NULL) {
        return false;
    }
    if (strlen(str) <= 1) {
        return false;
    }
    if (str[0] == '`' && str[strlen(str) - 1] == '`') {
        return true;
    }
    return false;
}

int get_fd_size(int fd)
{
    unsigned int size = 0;
    char buffer[BUFSIZ];
    int chars_read = 0;

    do {
        size += chars_read;
        chars_read = read(fd, buffer, BUFSIZ - 1);
    } while (chars_read != SYS_ERROR && chars_read != 0);
    if (chars_read == SYS_ERROR) {
        return SYS_ERROR;
    }
    return size;
}

static char *read_fd(int fd)
{
    char *buffer = NULL;
    //ssize_t chars_read = 0;
    //size_t len = 0;

    int filesize = get_fd_size(fd);

    if (filesize <= 0) {
        return my_strdup("file size");
        //return NULL;
    }
    buffer = malloc(sizeof(char) * (filesize + 1));
    if (buffer == NULL) {
        perror("read_fd malloc failed");
        return NULL;
    }
    if (read(fd, buffer, filesize) == SYS_ERROR) {
        perror("read_fd read failed");
        return my_strdup("test");
        //return NULL;
    }
    buffer[filesize] = '\0';
    chars_read = getline(&buffer, &len, fd);
    return buffer;
}

static int set_function(int fd, int output)
{
    if (fd == SYS_ERROR) {
        perror("open tmp file in get_backtick_output");
        return ERROR;
    }
    if (output == SYS_ERROR) {
        perror("dup in get_backtick_output");
        return ERROR;
    }
    printf("before dup\n");
    if (dup2(fd, STDOUT_FILENO) == SYS_ERROR) {
        perror("dup2 in get_backtick_output");
        return ERROR;
    }
    return SUCCESS;
}

char *get_backtick_output(shell_info_t *shell_info, char *cmd)
{
    char *cmd_result = NULL;
    int output = dup(STDOUT_FILENO);
    int fd = open("/tmp/", __O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);

    printf("before set function\n");
    if (set_function(fd, output) == ERROR) {
        return NULL;
    }
    printf("after set function\n");
    check_given_cmd_type(shell_info, cmd);
    cmd_result = read_fd(fd);
    close(fd);
    if (dup2(output, STDOUT_FILENO) == SYS_ERROR) {
        perror("dup2 get_backtick_output failed");
    }
    return cmd_result;
}
