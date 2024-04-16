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
#include "minishell1.h"
#include "my.h"

static int nb_ch_match(char *file, char *cmd)
{
    int i = 0;

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
            printf("[%s]\n", cur_file->d_name);
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

static void replace_user_input(char **user_input, char **args)
{
    int k = 0;

    *user_input = malloc(sizeof(char) * (args_len(args) + 1));
    for (int i = 0; args[i]; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            (*user_input)[k] = args[i][j];
            k++;
        }
    }
    (*user_input)[k] = '\0';
}

void auto_complete(char **user_input, shell_info *my_shell)
{
    char **args = NULL;
    char *new_cmd = NULL;
    char **paths = get_paths(my_shell->env);

    (*user_input)[my_strlen(*user_input) - 1] = '\0';
    args = my_pimp_str_to_wa(*user_input, " \t");
    for (int i = 1; paths && paths[i]; i++) {
        new_cmd = search_file(paths[i], args[0]);
        if (new_cmd)
            break;
    }
    args[0] = new_cmd;
    replace_user_input(user_input, args);
}
