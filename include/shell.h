/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** shell.h
*/

#ifndef SHELL
    #define SHELL

    #include "struct.h"
    #include "my.h"

    #define ERROR_EXIT 84
    #define ERROR 84
    #define SUCCESS_EXIT 0
    #define SUCCESS 0
    #define SYS_ERROR -1
    #define OPEN_ERROR -1
    #define INVALID_NULL_COMMAND -1
    #define READ_SIZE 1000000
    #define EXIT_STATUS_ERROR 139
    #define DEFAULT_SUCCESS_COLOR "green"
    #define DEFAULT_ERROR_COLOR "red"
    #define SIMPLE_REDIRECT_OUTPUT ">"
    #define DOUBLE_REDIRECT_OUTPUT ">>"
    #define PIPE "|"
    #define SIMPLE_REDIRECT_INPUT "<"
    #define DOUBLE_REDIRECT_INPUT "<<"
    #define HISTORIC_FILENAME "/tmp/42sh_cmd_save.txt"
    #define HISTORY_NB_SIZE 6
    #define MAX_LENGTH 1000000
    //ASCI chars
    #define ESC 27
    #define DEL 127
    #define EOT 4
    //special printf values
    #define CLEAR "\e[1;1H\e[2J"
    #define MOVE_LEFT "\033[1D"
    #define MOVE_RIGHT "\033[1C"
    #define MOVE_UP "\033[1A"
    #define MOVE_DOWN "\033[1B"

int my_sh(char **env);
char **get_paths(char **env);
void disp_env(char **args, shell_info_t *my_shell);
void change_dir(char **args, shell_info_t *my_shell);
void set_env(char **args, shell_info_t *my_shell);
void set_env_no_disp(char **args, shell_info_t *my_shell);
void unset_env(char **args, shell_info_t *my_shell);
char *get_name(char **env, int index);
void command_handling(shell_info_t *my_shell, char **args);
void set_color(char **args, shell_info_t *my_shell);
int valid_color(char *color);
char **get_args(shell_info_t *my_shell);
char **check_redirect(char **args, shell_info_t *my_shell);
void check_cmd_type(shell_info_t *my_shell);
bool check_pipe(char *cmd, shell_info_t *my_shell);
char ***get_all_cmd(char ***all_cmds, char **args);
bool valid_redirect(char **cmds);
char *get_user_input(shell_info_t *my_shell);
bool no_env(char **env);
void my_alias(char **args, shell_info_t *my_shell);
alias_t *init_alias(void);
int exec_alias(shell_info_t *my_shell, char *args);
void exec_cmd(char **args, shell_info_t *my_shell);
char **check_dollar(char **args, shell_info_t *my_shell);

// --> exec cmds
void check_given_cmd_type(shell_info_t *my_shell, char *cmd);
bool built_in_command(char **args, shell_info_t *my_shell);

// --> historic
void display_historic(char **args, shell_info_t *my_shell);
int add_command_to_save(char const *cmd);
linked_list_t *get_array_from_prev_cmd(char *current_cmd);
int my_special_getnbr(char const *str);
int read_history(char const *filename);

// --> linked_list
linked_list_t *create_list_from_array(char **array);

// --> file
int get_file_size(char const *filename);
int open_append(char const *filename);
int read_open(char const *filename);
char *get_file_content(char const *filename);

// --> time
char *get_current_time(void);

// --> backtick
void replace_backtick(char **str, shell_info_t *my_shell);

// --> and or
bool check_and_or(char *cmd, shell_info_t *my_shell);

// --> line parsing
char *get_prompt(shell_info_t *my_shell);
void delete_string(shell_input_t *user_input);
void insert_string(shell_input_t *user_input, char *to_insert);

// --> command error
void cmd_not_found(char **args, shell_info_t *my_shell,
    char *cmd_path, char **paths);
void check_seg_fault(int wstatus, shell_info_t *my_shell);
void disp_err_message(char const *command);

// --> command exec
void exec_no_pipe(char *cmd, shell_info_t *my_shell);

// --> globbing
int get_globbing_nb(char **command);
void globbing(char **commands, shell_info_t *my_shell);

// --> gpt
void gpt(char **args, shell_info_t *my_shell);

// --> auto-complete
void auto_complete(shell_input_t *user_input, shell_info_t *my_shell);

#endif
