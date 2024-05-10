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
    #define ALIAS_PATH "/tmp/42rc.txt"
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

// --> shell
int my_sh(char **env);
int end_shell(shell_info_t *my_shell);
void disp_actual_dir(shell_info_t *my_shell);

// --> init
shell_info_t *init_shell_info_t(char **env);
void disp_actual_dir(shell_info_t *my_shell);

// --> env
void set_env(char **args, shell_info_t *my_shell);
void set_env_no_disp(char **args, shell_info_t *my_shell);
void unset_env(char **args, shell_info_t *my_shell);
void disp_env(char **args, shell_info_t *my_shell);
bool no_env(char **env);
bool is_valid_arg(char *arg, char *cmd);
char *get_name(char **env, int index);

// --> alias
void my_alias(char **args, shell_info_t *my_shell);
alias_t *init_alias(void);
int exec_alias(shell_info_t *my_shell, char *args);
alias_t *change_alias_cmd(char **args, shell_info_t *my_shell);
int alias_loop_check(shell_info_t *my_shell, char *args);

// --> color
void set_color(char **args, shell_info_t *my_shell);
int valid_color(char *color);
void disp_color_help(void);

// --> redirections
char **check_redirect(char **args, shell_info_t *my_shell);
bool valid_redirect(char **cmds);

// --> cd
void change_dir(char **args, shell_info_t *my_shell);

// --> exec cmds
void check_given_cmd_type(shell_info_t *my_shell, char *cmd);
void exec_cmd(char **args, shell_info_t *my_shell);
void command_handling(shell_info_t *my_shell, char **args);
bool built_in_command(char **args, shell_info_t *my_shell);
char **get_paths(char **env);
void check_cmd_type(shell_info_t *my_shell);
bool check_pipe(char *cmd, shell_info_t *my_shell);

// --> historic
void display_historic(char **args, shell_info_t *my_shell);
int add_command_to_save(char const *cmd);
linked_list_t *get_array_from_prev_cmd(char *current_cmd);
int my_special_getnbr(char const *str);
int read_history(char const *filename);
char *check_if_historic(char **cmd, shell_info_t *my_shell);
char *find_last_cmd(void);
char *get_the_n_cmd(char *str);
void remove_from_file(char **, unsigned int);
char *find_cmd_in_line(char *);
char *not_found_error(char const *event);
char *get_cmd_with_str(char *str);
int check_buffer(char const *buffer, int fd);

// --> linked_list
linked_list_t *create_list_from_array(char **array);
void free_list(linked_list_t *list);

// --> file
int get_file_size(char const *filename);
int open_append(char const *filename);
int read_open(char const *filename);
char *get_file_content(char const *filename);

// --> job control
void background_process(char **args, shell_info_t *my_shell);
void foreground_process(char **args, shell_info_t *my_shell);
void signal_child(int pid, int signal, shell_info_t *my_shell);
process_t *add_job(int pid, shell_info_t *my_shell, char *cmd);
void remove_job(int pid, shell_info_t *my_shell);
void wait_for_pid(int pid, shell_info_t *my_shell);
bool job_exist(int process_nb, shell_info_t *my_shell);
process_t *get_job_from_id(int nb, shell_info_t *my_shell);
process_t *get_job_from_pid(int pid, shell_info_t *my_shell);
void sig_handler(int signum);
void end_job_control(shell_info_t *my_shell);
void sigstp_handler(int signum);

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
char *get_user_input(shell_info_t *my_shell);
char **get_args(shell_info_t *my_shell);
char ***get_all_cmd(char ***all_cmds, char **args);

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

// --> alias
void my_alias(char **args, shell_info_t *my_shell);
int exec_alias(shell_info_t *my_shell, char *args);
void del_alias(char **args, shell_info_t *my_shell);
int exec_alias_loop(shell_info_t *my_shell, alias_t *list);
int alias_loop(char *args, shell_info_t *my_shell);

// --> gpt
void gpt(char **args, shell_info_t *my_shell);

// --> auto-complete
void auto_complete(shell_input_t *user_input, shell_info_t *my_shell);

// --> local varaiables
void set_local(char **args, shell_info_t *my_shell);
void unset_local(char **args, shell_info_t *my_shell);
char **replace_var(char **args, shell_info_t *my_shell);

// --> tests
char **create_strstr(char *s1, char *s2, char *s3, char *s4);


#endif
