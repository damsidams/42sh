/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** struct.h
*/

#ifndef STRUCT_H
    #define STRUCT_H
    #include <stdbool.h>

typedef struct alias_s {
    char *alias_cmd;
    char *real_cmd;
    struct alias_s *next;
}alias_t;

typedef struct shell_info_t_s {
    char **env;
    char *last_path;
    int exit_status;
    int *color;
    bool exit_shell;
    bool is_a_tty;
    int stdout_cpy;
    int stdin_cpy;
    alias_t *list_alias;
} shell_info_t;

enum sep_type {
    And,
    Or,
    End
};

#endif
