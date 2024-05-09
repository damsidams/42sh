/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
** File description:
** get_input_getline.c
*/

#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "struct.h"

static int no_tty_prompt(char **user_input, size_t *bufsize,
    shell_info_t *my_shell)
{
    ssize_t line_size = 0;

    line_size = getline(user_input, bufsize, stdin);
    if (line_size > 0)
        (*user_input)[line_size - 1] = '\0';
    if (line_size == -1) {
        if (my_shell->is_a_tty)
            mini_printf("exit\n");
        return -1;
    }
    if (line_size == -1 && my_strlen(*user_input) == 0)
        return 0;
    return 1;
}

char *no_entry_input(shell_info_t *my_shell)
{
    size_t bufsize = 0;
    ssize_t line_size = 0;
    char *user_input = NULL;

    while (line_size == 0) {
        line_size = no_tty_prompt(&user_input, &bufsize, my_shell);
        if (line_size == -1) {
            my_shell->exit_shell = true;
            free(user_input);
            return NULL;
        }
        if (my_strlen(user_input) == 0) {
            free(user_input);
            return NULL;
        }
    }
    return user_input;
}
