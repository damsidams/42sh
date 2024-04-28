/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** my_sh.c
*/

#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "shell.h"
#include "struct.h"


static char *get_path_to_display(char *actual_dir, int index)
{
    int len = 0;
    int i = index;
    char *path_to_display = NULL;

    while (actual_dir[i] != '\0') {
        i++;
        len++;
    }
    path_to_display = malloc(sizeof(char) * len + 1);
    if (path_to_display == NULL) {
        perror("get_path_to_display malloc");
        return NULL;
    }
    for (int j = 0; actual_dir[index] != '\0'; j++) {
        path_to_display[j] = actual_dir[index];
        index++;
    }
    path_to_display[len] = '\0';
    return path_to_display;
}

static void disp_error(shell_info_t *my_shell, char *path)
{
    if (my_shell->exit_status == EXIT_STATUS_ERROR) {
        mini_printf("\u203C\033[1;%dm [%s]$\033[0m ",
            my_shell->color[1], path);
    } else {
        mini_printf("\u274C\033[1;%dm [%s]$\033[0m ",
            my_shell->color[1], path);
    }
}

static void set_index(char const *actual_dir, int *index)
{
    for (int i = 0; actual_dir[i] != '\0'; i++) {
        if (actual_dir[i] == '/')
            *index = i;
    }
    *index += 1;
}

static void disp_actual_dir(shell_info_t *my_shell)
{
    char *actual_dir = NULL;
    char *path = NULL;
    int index = 0;

    actual_dir = getcwd(actual_dir, BUFSIZ);
    set_index(actual_dir, &index);
    path = get_path_to_display(actual_dir, index);
    if (my_shell && my_shell->exit_status != 0
        && my_shell->exit_status != EXIT_STATUS_ERROR) {
        disp_error(my_shell, path);
    } else if (my_shell) {
        mini_printf("\u2705\033[1;%dm [%s]$\033[0m ", my_shell->color[0],
            path);
    } else {
        mini_printf("\u2705\033[1;32m [%s]$\033[0m ", path);
    }
    free(path);
    free(actual_dir);
}

void sig_handler(int signum)
{
    (void)signum;
    write(0, "\n", 1);
    disp_actual_dir(NULL);
    return;
}

int my_sh(char **env)
{
    shell_info_t *my_shell = init_shell_info_t(env);
    int stdout_cpy = dup(STDOUT_FILENO);
    int stdin_cpy = dup(STDIN_FILENO);

    signal(SIGINT, sig_handler);
    while (!my_shell->exit_shell) {
        if (my_shell->is_a_tty) {
            disp_actual_dir(my_shell);
        }
        check_cmd_type(my_shell);
        dup2(stdout_cpy, STDOUT_FILENO);
        dup2(stdin_cpy, STDIN_FILENO);
        my_shell->stdout_cpy = stdout_cpy;
    }
    return end_shell(my_shell);
}
