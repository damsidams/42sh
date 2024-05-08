/*
** EPITECH PROJECT, 2024
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
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
    #define HISTORIC_ERROR -1
    #define BACKTICK_ERROR -1
    #define SYS_ERROR -1
    #define OPEN_ERROR -1
    #define NOT_ALLOWED 1
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
    #define HISTORY_CHAR '!'
    #define BACKTICK '`'
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
    #define MAGIC_STRING "(75787tokf.wzy:htuhiu)"

int my_sh(char **env);
void command_handling(shell_info_t *my_shell, char **args);
char **get_args(shell_info_t *my_shell);
char **check_redirect(char **args, shell_info_t *my_shell);
void check_cmd_type(shell_info_t *my_shell);
bool check_pipe(char *cmd, shell_info_t *my_shell);
char ***get_all_cmd(char ***all_cmds, char **args);
bool valid_redirect(char **cmds);
char *get_user_input(shell_info_t *my_shell);
char **create_strstr(char *s1, char *s2, char *s3, char *s4);
int end_shell(shell_info_t *my_shell);

// --> built in functions
void change_dir(char **args, shell_info_t *my_shell);

// -->env
void disp_env(char **args, shell_info_t *my_shell);
void set_env(char **args, shell_info_t *my_shell);
void unset_env(char **args, shell_info_t *my_shell);
bool no_env(char **env);
char *get_name(char **env, int index);
char **get_paths(char **env);

// --> colors
void set_color(char **args, shell_info_t *my_shell);
int valid_color(char *color);

// --> init
shell_info_t *init_shell_info_t(char **env);

// --> alias
void my_alias(char **args, shell_info_t *my_shell);
alias_t *init_alias(void);
int exec_alias(shell_info_t *my_shell, char *args);
bool no_env(char **env);
void my_alias(char **args, shell_info_t *my_shell);
alias_t *init_alias(void);
int exec_alias(shell_info_t *my_shell, char *args);
void exec_cmd(char **args, shell_info_t *my_shell);
int end_shell(shell_info_t *my_shell);

// --> exec cmds
void check_given_cmd_type(shell_info_t *my_shell, char *cmd);
bool built_in_command(char **args, shell_info_t *my_shell);
void exec_cmd(char **args, shell_info_t *my_shell);

// --> historic
void display_historic(char **args, shell_info_t *my_shell);
int add_command_to_save(char const *cmd);
linked_list_t *get_array_from_prev_cmd(char *current_cmd);
int my_special_getnbr(char const *str);
int read_history(char const *filename);
char *check_if_historic(char *cmd, shell_info_t *my_shell);
char *find_last_cmd(void);
char *get_the_n_cmd(char *str);
void remove_from_file(char **, unsigned int);
char *find_cmd_in_line(char *);
char *not_found_error(char const *event);
char *get_cmd_with_str(char *str);
int check_buffer(char const *buffer, int fd);

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
char **replace_backtick(char **cmd, shell_info_t *my_shell);
char *get_backtick_output(shell_info_t *shell_info, char *cmd);

// --> parentheses
bool exec_parentheses(shell_info_t *my_shell, char **cmd);
bool parentheses_badly_placed(char const *cmd);
bool check_parentheses_order(char const *str);
bool par_around(char const *str);

// --> and or
bool check_and_or(char *cmd, shell_info_t *my_shell);

// --> line parsing
char *get_prompt(shell_info_t *my_shell);
char *no_entry_input(shell_info_t *my_shell);

// -->input manip
void delete_char(shell_input_t *user_input);
void delete_string(shell_input_t *user_input);
void insert_string(shell_input_t *user_input, char *to_insert);
void insert_char(shell_input_t *user_input, char c);


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

// --> return_value
int is_dollar(char *args);
char **check_dollar(char **args, shell_info_t *my_shell);

// --> alias
void my_alias(char **args, shell_info_t *my_shell);
alias_t *init_alias(void);
int exec_alias(shell_info_t *my_shell, char *args);
void del_alias(char **args, shell_info_t *my_shell);
int exec_alias_loop(shell_info_t *my_shell, alias_t *list);
int alias_loop(char *args, shell_info_t *my_shell);

// --> gpt
void gpt(char **args, shell_info_t *my_shell);

// --> auto-complete
void auto_complete(shell_input_t *user_input, shell_info_t *my_shell);

#endif
