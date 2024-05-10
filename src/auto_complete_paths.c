/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** auto complete paths
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

static char *get_clean_path(char **args, int len)
{
    char *path = strdup(args[len - 1]);
    int cpt = strlen(path);

    for (; path[cpt] != '/' && cpt >= 0; cpt--) {
        if (cpt == 0) {
            free(path);
            return strdup(args[len - 1]);
        }
    }
    path[cpt + 1] = '\0';
    return path;
}

static char *get_last_path_word(char **args, int len)
{
    char *word = args[len - 1];
    int cpt = strlen(word);

    for (; word[cpt] != '/' && cpt >= 0; cpt--) {
        if (cpt == 0) {
            return args[len - 1];
        }
    }
    for (int i = 0; i < cpt; i++) {
        word++;
    }
    if (word[1] != '\0')
        word++;
    return word;
}

static DIR *open_dir(char **args, char *cwd, int len)
{
    char *path = get_clean_path(args, len);
    DIR *dir = NULL;

    if (path[0] != '/') {
        path = my_str_append(my_strcat(cwd, "/"), path);
    }
    dir = opendir(path);
    free(path);
    return dir;
}

static void auto_complete_paths_end(char **args, shell_input_t *user_input,
    linked_list_t *match, shell_info_t *my_shell)
{
    char *cpy = NULL;
    int list_len = 0;
    int len = my_strstrlen(args);

    cpy = args[len - 1];
    list_len = list_size(match);
    if (list_len > 1) {
        args[len - 1] = get_element(match, my_shell);
    }
    if (list_len == 1) {
        args[len - 1] = strdup(match->value);
        free_basic_list(match);
    }
    if (list_len >= 1) {
        replace_user_input(user_input, args);
        free_auto_complete(cpy, args);
    }
}

static void search_match(char **args, char *cmd, struct dirent *cur_file,
    linked_list_t **match)
{
    char *final = get_clean_path(args, my_strstrlen(args));
    char *word = get_last_path_word(args, my_strstrlen(args));
    bool good = false;

    if (strcmp(final, args[my_strstrlen(args) - 1]) == 0)
        good = true;
    if (final[strlen(final) - 1] == '/' && cmd[strlen(cmd) - 1] == '/') {
        push_to_list(match, my_strcat(final, cur_file->d_name));
    }
    if (nb_ch_match(cur_file->d_name, word) == my_strlen(word) && !good) {
        push_to_list(match, my_strcat(final, cur_file->d_name));
    }
    if (nb_ch_match(cur_file->d_name, cmd) == my_strlen(cmd) && good) {
        push_to_list(match, strdup(cur_file->d_name));
    }
}

static void create_match_list_paths(linked_list_t **match, DIR *bin_dir,
    char *cmd, char **args)
{
    struct dirent *cur_file = NULL;

    cur_file = readdir(bin_dir);
    while (cur_file != NULL) {
        if (my_strcmp(cur_file->d_name, ".") == 0 ||
            my_strcmp(cur_file->d_name, "..") == 0) {
            cur_file = readdir(bin_dir);
            continue;
        }
        search_match(args, cmd, cur_file, match);
        cur_file = readdir(bin_dir);
    }
    closedir(bin_dir);
}

void auto_complete_paths(char **args, shell_input_t *user_input,
    shell_info_t *my_shell)
{
    int len = my_strstrlen(args);
    char *cwd = NULL;
    DIR *dir;
    linked_list_t *match = NULL;
    char *word = strdup(get_last_path_word(args, len));

    if (len <= 1)
        return;
    if (my_shell->base_auto_completion != NULL)
        word = strdup(my_shell->base_auto_completion);
    cwd = getcwd(cwd, BUFSIZ);
    dir = open_dir(args, cwd, len);
    if (dir == NULL)
        dir = opendir(cwd);
    create_match_list_paths(&match, dir, word, args);
    auto_complete_paths_end(args, user_input, match, my_shell);
    free(word);
}
