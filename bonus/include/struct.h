/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** struct.h
*/

#ifndef MINISHELL_1_STRUCT
    #define MINISHELL_1_STRUCT
    #include <stdbool.h>

typedef struct shell_info_t {
    char **env;
    char *last_path;
    int exit_status;
    int *color;
    bool exit_shell;
    bool is_a_tty;
    int stdout_cpy;
    int stdin_cpy;
} shell_info;

#endif /* MINISHELL_1_STRUCT */
