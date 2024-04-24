/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** struct.h
*/

#ifndef STRUCT_H
    #define STRUCT_H
    #include <stdbool.h>

typedef struct shell_info_t_s {
    char **env;
    char *last_path;
    int exit_status;
    int *color;
    bool exit_shell;
    bool is_a_tty;
    int stdout_cpy;
    int stdin_cpy;
} shell_info_t;

typedef struct alias_s {
    char *alias_cmd;
    char *real_cmd;
    struct alias_s *next;
}alias_t;

typedef struct list {
    alias_t *premier;
}list_t;

enum sep_type {
    And,
    Or,
    End
};

#endif
        display_list_alias(list_alias);
