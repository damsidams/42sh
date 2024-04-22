/*
** EPITECH PROJECT, 2024
** globbing
** File description:
** all globbing related functions
*/

#include <glob.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "shell.h"

static int array_size(char **array)
{
    int res = 0;

    while (array[res] != NULL)
        res++;
    return res;
}

static int is_bracket(char const *command, int i)
{
    if (command[i] == ']')
        return 0;

    for (int j = i; command[j] != '\0'; j++) {
        if (command[j] == ']')
            return 1;
    }
    return 0;
}

static int count_globbing(char const *command)
{
    int res = 0;

    for (int i = 0; command[i] != '\0'; i++) {
        switch (command[i]) {
        case '?':
            res += 1;
            break;
        case '*':
            res += 1;
            break;
        case '[':
            res += is_bracket(command, i + 1);
        }
    }
    return res;
}

int get_globbing_nb(char **command)
{
    int res = 0;

    for (int i = 0; command[i] != NULL; i++) {
        if (count_globbing(command[i]) != 0)
            res += 1;
    }
    return res;
}

static void fill_globbing_struct(glob_t *globbing_buffer, char *command)
{
    static int command_params = 0;

    if (count_globbing(command) != 0) {
        if (command_params == 0) {
            glob(command, GLOB_DOOFFS, NULL, globbing_buffer);
            command_params += 1;
        } else
            glob(command, GLOB_DOOFFS | GLOB_APPEND, NULL, globbing_buffer);
    }
}

static void fill_globbing_struct_commands(glob_t *globbing_buffer, char *command)
{
    static int command_params = 0;

    if (count_globbing(command) == 0) {
        globbing_buffer->gl_pathv[command_params] = strdup(command);
        command_params++;
    }
}

void globbing(char **commands, shell_info_t *my_shell)
{
    glob_t globbing_buffer;
    int command_nb = array_size(commands) - get_globbing_nb(commands);

    globbing_buffer.gl_offs = command_nb;
    for (int i = 0; commands[i] != NULL; i++)
        fill_globbing_struct(&globbing_buffer, commands[i]);
    for (int i = 0; commands[i] != NULL; i++)
        fill_globbing_struct_commands(&globbing_buffer, commands[i]);
    if (globbing_buffer.gl_pathc == 0) {
        dprintf(2, "%s: No match.\n", commands[0]);
        my_shell->exit_status = 1;
    } else {
        if (fork() == 0) {
            execvp(commands[0], &globbing_buffer.gl_pathv[0]);
            exit(0);
        } else {
            wait(NULL);
            my_shell->exit_status = 0;
        }
    }
}
