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
#include <sys/wait.h>
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

static char *read_fd(int fd)
{
    char *buffer = NULL;
    int filesize = READ_SIZE;
    int chars_read = 0;

    if (filesize <= 0) {
        return my_strdup("file size");
    }
    buffer = calloc(filesize + 1, sizeof(char));
    if (buffer == NULL) {
        perror("read_fd calloc failed");
        return NULL;
    }
    chars_read = read(fd, buffer, filesize);
    if (chars_read == SYS_ERROR) {
        perror("read_fd read failed");
        return my_strdup("test");
    }
    buffer[chars_read] = '\0';
    return buffer;
}

static int set_function(int *fd, int output)
{
    if (pipe(fd) == SYS_ERROR) {
        perror("pipe in set_function failed");
        return ERROR;
    }
    if (output == SYS_ERROR) {
        perror("dup in get_backtick_output");
        return ERROR;
    }
    return SUCCESS;
}

static void child(int fd, shell_info_t *my_shell, char *cmd)
{
    dup2(fd, STDOUT_FILENO);
    check_given_cmd_type(my_shell, cmd);
    exit(0);
}

char *get_backtick_output(shell_info_t *shell_info, char *cmd)
{
    char *cmd_result = NULL;
    int output = dup(STDOUT_FILENO);
    int fd[2] = {0};
    pid_t pid;

    if (set_function(fd, output) == ERROR) {
        return NULL;
    }
    pid = fork();
    if (pid == SYS_ERROR) {
        return NULL;
    }
    if (pid == 0) {
        child(fd[1], shell_info, cmd);
    }
    close(fd[1]);
    cmd_result = read_fd(fd[0]);
    waitpid(pid, NULL, 0);
    close(fd[0]);
    return cmd_result;
}
