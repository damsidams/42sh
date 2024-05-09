/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** background for the shell processes
*/

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "struct.h"

static void background_process_args(char **args, shell_info_t *my_shell)
{
    process_t *process = NULL;
    int process_nb = 0;

    if (args[1][0] == '%') {
        process_nb = my_getnbr(args[1]);
        if (job_exist(process_nb, my_shell)) {
            process = get_job_from_id(process_nb, my_shell);
            signal_child(process->pid, 0, NULL);
            kill(process->pid, SIGCONT);
            return;
        } else {
            puts("bg: No such job.");
        }
    }
}

void background_process(char **args, shell_info_t *my_shell)
{
    int len = my_strstrlen(args);
    process_t *process = 0;

    if (len == 1 && my_shell->stopped_pid != my_shell->shell_pgid) {
        printf("bg : %d\n", my_shell->stopped_pid);
        signal_child(my_shell->stopped_pid, 0, NULL);
        kill(my_shell->stopped_pid, SIGCONT);
        process = get_job_from_pid(my_shell->stopped_pid, my_shell);
        printf("[%d]\t%s &\n", process->nb, process->cmd);
    }
    if (len == 2) {
        background_process_args(args, my_shell);
    }
}
