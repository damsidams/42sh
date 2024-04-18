/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Function related to backtick
*/

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

static char *read_fd(int write_fd, int read_fd)
{
    char *buffer = malloc(sizeof(char) * (BUFSIZE + 1));
    int chars_read = 0;

    do {
        chars_read += read(fd, buffer, BUFSIZ);
    } while (chars_read != SYS_ERROR && chars_read != 0);
    if (chars_read == SYS_ERROR || chars_read == 0) {
        return NULL;
    }
    buffer = realloc(buffer, chars_read + 1);
    if (buffer == NULL) {
        perror("read_fd realloc failed");
        return NULL;
    }
    if (read(fd, buffer, chars_read) == SYS_ERROR) {
        perror("read_fd read failed");
        return NULL;
    }
    buffer[chars_read] = '\0';
    return buffer;
}

static int set_function(int *fd, int output)
{
    if (pipe(fd) == SYS_ERROR) {
        perror("pipe in get_backtick_output failed");
        return ERROR;
    }
    if (output == SYS_ERROR) {
        perror("dup in get_backtick_output");
        return ERROR;
    }
    if (dup2(fd[1], STDOUT_FILENO) == SYS_ERROR) {
        perror("dup2 in get_backtick_output");
        return ERROR;
    }
    return SUCCESS;
}

char *get_backtick_output(shell_info_t *shell_info, char *cmd)
{
    char *cmd_result = NULL;
    int output = dup(STDOUT_FILENO);
    int fd[2];

    if (set_function(fd, output) == ERROR) {
        return NULL;
    }
    check_given_cmd_type(shell_info, cmd);
    cmd_result = read_fd(fd[1], fd[0]);
    close(fd[1]);
    close(fd[0]);
    if (dup2(output, STDOUT_FILENO) == SYS_ERROR) {
        perror("dup2 get_backtick_output failed");
    }
    return cmd_result;
}
