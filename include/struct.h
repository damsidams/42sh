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

typedef struct process_t_s {
    int nb;
    int pid;
}process_t;

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
    process_t *jobs;
    int shell_pgid;
    int stopped_pid;
} shell_info_t;

typedef struct linked_list_s {
    char *value;
    struct linked_list_s *prev;
    struct linked_list_s *next;
} linked_list_t;

typedef struct shell_input_s {
    int index;
    int cursor;
    char *input;
} shell_input_t;

enum sep_type {
    And,
    Or,
    End
};

#endif
