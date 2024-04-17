/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** minishell1.h
*/

#ifndef MINISHELL_1
    #define MINISHELL_1
    #define ERROR_EXIT 84
    #define SUCCESS_EXIT 0
    #define DEFAULT_SUCCESS_COLOR "green"
    #define DEFAULT_ERROR_COLOR "red"
    #define SIMPLE_REDIRECT_OUTPUT ">"
    #define DOUBLE_REDIRECT_OUTPUT ">>"
    #define PIPE "|"
    #define SIMPLE_REDIRECT_INPUT "<"
    #define DOUBLE_REDIRECT_INPUT "<<"
    #define API_KEY "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"
    #define JSON_BUFFER_LENGHT 4096
    #include "struct.h"

int my_sh(char **env);
void disp_env(char **args, shell_info *my_shell);
void change_dir(char **args, shell_info *my_shell);
void set_env(char **args, shell_info *my_shell);
void set_env_no_disp(char **args, shell_info *my_shell);
void unset_env(char **args, shell_info *my_shell);
char *get_name(char **env, int index);
void command_handling(shell_info *my_shell, char **args);
void set_color(char **args, shell_info *my_shell);
int valid_color(char *color);
char **get_args(shell_info *my_shell);
char **check_redirect(char **args, shell_info *my_shell);
void check_cmd_type(shell_info *my_shell);
bool check_pipe(char *cmd, shell_info *my_shell);
char ***get_all_cmd(char ***all_cmds, char **args);
bool valid_redirect(char **cmds);
char *get_user_input(shell_info *my_shell);
bool no_env(char **env);
void gpt(char **args, shell_info *my_shell);

#endif /* MINISHELL_1 */
