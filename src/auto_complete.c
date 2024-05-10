/*
** EPITECH PROJECT, 2024
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
** File description:
** auto completion
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "struct.h"
#include "shell.h"
#include "my.h"

int nb_ch_match(char *file, char *cmd)
{
    int i = 0;

    if (!file || !cmd)
        return -1;
    for (i = 0; file[i] != '\0' && cmd[i] != '\0'; i++) {
        if (file[i] != cmd[i])
            break;
    }
    return i;
}

static void set_base_auto_completion_cmd(shell_info_t *my_shell,
    shell_input_t *user_input)
{
    char **args = my_pimp_str_to_wa(user_input->input, " \t");

    if (my_shell->base_auto_completion == NULL
        && my_shell->auto_completion_offset == 1)
        my_shell->base_auto_completion = strdup(args[0]);
    free_str_array(args);
}

char *get_element(linked_list_t *match, shell_info_t *my_shell)
{
    char *word = NULL;
    linked_list_t *match_ptr = match;

    if (list_size(match) > 1) {
        for (int i = 1; i < my_shell->auto_completion_offset
        && match->next != NULL; i++) {
            match = match->next;
        }
        word = strdup(match->value);
    }
    free_basic_list(match_ptr);
    return word;
}

void replace_user_input(shell_input_t *user_input, char **args)
{
    delete_string(user_input);
    for (int i = 0; args[i]; i++) {
        insert_string(user_input, args[i]);
        insert_char(user_input, ' ');
    }
}

static void set_base_auto_completion_paths(shell_info_t *my_shell,
    shell_input_t *user_input)
{
    char **args = my_pimp_str_to_wa(user_input->input, " \t");
    int len = my_strstrlen(args);

    if (my_shell->base_auto_completion == NULL
        && my_shell->auto_completion_offset == 1)
        my_shell->base_auto_completion = strdup(args[len - 1]);
    free_str_array(args);
}

void auto_complete(shell_input_t *user_input, shell_info_t *my_shell)
{
    char **args = NULL;
    int len = 0;

    if (!user_input->input)
        return;
    user_input->input[my_strlen(user_input->input)] = '\0';
    args = my_pimp_str_to_wa(user_input->input, " \t");
    len = my_strstrlen(args);
    if (len == 1) {
        set_base_auto_completion_cmd(my_shell, user_input);
        auto_complete_cmd(args, user_input, my_shell);
        return;
    } else {
        set_base_auto_completion_paths(my_shell, user_input);
        auto_complete_paths(args, user_input, my_shell);
    }
}
