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
#include <fcntl.h>
#include <sys/stat.h>
#include "struct.h"
#include "shell.h"
#include "my.h"

static int nb_ch_match(char *file, char *cmd)
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

static char *search_file(char *cmd_path, char *cmd)
{
    DIR *bin_dir = opendir(cmd_path);
    struct dirent *cur_file = NULL;

    if (!bin_dir)
        return NULL;
    cur_file = readdir(bin_dir);
    while (cur_file != NULL) {
        if (my_strcmp(cur_file->d_name, ".") == 0 ||
            my_strcmp(cur_file->d_name, "..") == 0) {
            cur_file = readdir(bin_dir);
            continue;
        }
        if (nb_ch_match(cur_file->d_name, cmd) == my_strlen(cmd)) {
            return cur_file->d_name;
        }
        cur_file = readdir(bin_dir);
    }
    closedir(bin_dir);
    return NULL;
}

static int args_len(char **args)
{
    int len = 0;

    for (int i = 0; args[i]; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            len++;
        }
    }
    return len;
}

static void replace_user_input(shell_input_t *user_input, char **args)
{
    delete_string(user_input);
    for (int i = 0; args[i]; i++) {
        insert_string(user_input, args[i]);
    }
}

void auto_complete(shell_input_t *user_input, shell_info_t *my_shell)
{
    char **args = NULL;
    char *new_cmd = NULL;
    char **paths = get_paths(my_shell->env);

    if (!user_input->input)
        return;
    user_input->input[my_strlen(user_input->input) - 1] = '\0';
    args = my_pimp_str_to_wa(user_input->input, " \t");
    for (int i = 1; paths && paths[i]; i++) {
        new_cmd = search_file(paths[i], args[0]);
        if (new_cmd)
            break;
    }
    args[0] = new_cmd;
    replace_user_input(user_input, args);
}
