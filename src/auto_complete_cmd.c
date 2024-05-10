/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** auto complete commands
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

static void create_match_list(linked_list_t **match, DIR *bin_dir, char *cmd)
{
    struct dirent *cur_file = NULL;

    cur_file = readdir(bin_dir);
    while (cur_file != NULL) {
        if (my_strcmp(cur_file->d_name, ".") == 0 ||
            my_strcmp(cur_file->d_name, "..") == 0) {
            cur_file = readdir(bin_dir);
            continue;
        }
        if (nb_ch_match(cur_file->d_name, cmd) == my_strlen(cmd)) {
            push_to_list(match, cur_file->d_name);
        }
        cur_file = readdir(bin_dir);
    }
    closedir(bin_dir);
}

static char *search_file(char *cmd_path, char *cmd, shell_info_t *my_shell)
{
    DIR *bin_dir = opendir(cmd_path);
    linked_list_t *match = NULL;
    char *word = NULL;

    if (my_shell->base_auto_completion != NULL) {
        cmd = my_shell->base_auto_completion;
    }
    if (!bin_dir)
        return NULL;
    create_match_list(&match, bin_dir, cmd);
    if (list_size(match) > 1)
        return get_element(match, my_shell);
    if (list_size(match) == 1) {
        word = strdup(match->value);
        free_basic_list(match);
        return word;
    }
    free_basic_list(match);
    return NULL;
}

static void free_auto_complete(char *word, char **args)
{
    free(word);
    for (int i = 0; args[i]; i++) {
        free(args[i]);
    }
}

void auto_complete_cmd(char **args, shell_input_t *user_input,
    shell_info_t *my_shell)
{
    char *new_cmd = NULL;
    char *word = NULL;
    char **paths = get_paths(my_shell->env);

    for (int i = 1; paths && paths[i]; i++) {
        new_cmd = search_file(paths[i], args[0], my_shell);
        if (new_cmd)
            break;
    }
    word = args[0];
    args[0] = new_cmd;
    replace_user_input(user_input, args);
    free_auto_complete(word, args);
    free_str_array(paths);
}
