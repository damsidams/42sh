/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** user_input.c
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

static int get_prompt(char **user_input,
    size_t *bufsize, shell_info_t *my_shell)
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
    add_command_to_save(*user_input);
    return 1;
}

char *get_user_input(shell_info_t *my_shell)
{
    size_t bufsize = 0;
    ssize_t line_size = 0;
    char *user_input = NULL;

    while (line_size == 0) {
        line_size = get_prompt(&user_input, &bufsize, my_shell);
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

char ***get_all_cmd(char ***all_cmds, char **args)
{
    int num_cmds = 0;
    char **args_cpy = my_str_array_dup(args);

    for (int i = 0; args[i]; i++)
        num_cmds++;
    all_cmds = malloc((num_cmds + 1) * sizeof(char **));
    for (int i = 0; i <= num_cmds; i++)
        all_cmds[i] = NULL;
    for (int i = 0; args_cpy[i]; i++)
        all_cmds[i] = my_pimp_str_to_wa(args_cpy[i], " ");
    free_str_array(args_cpy);
    return all_cmds;
}

static bool no_cmd(char *user_input)
{
    for (int i = 0; user_input[i] != '\0'; i++) {
        if (user_input[i] != ' ' && user_input[i] != '\t')
            return false;
    }
    return true;
}

char **get_args(shell_info_t *my_shell)
{
    char *user_input = get_user_input(my_shell);
    char *user_input_cpy = my_strdup(user_input);
    char **args = NULL;

    if (!user_input || no_cmd(user_input))
        return NULL;
    if (my_strlen(user_input) != 0)
        args = my_pimp_str_to_wa(user_input, ";");
    if (my_strcmp(args[0], "exit") == 0) {
        mini_printf("exit\n");
        my_shell->exit_shell = true;
        my_shell->exit_status = 0;
        args = NULL;
    }
    my_free_n_str(2, user_input, user_input_cpy);
    return args;
}
