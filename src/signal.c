/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** All signal handlers.
*/

#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "struct.h"

static void signal_child_suspend(int signal, int current_pid,
    shell_info_t *shell)
{
    if (signal == SIGTSTP && shell->shell_pgid != current_pid) {
        printf("Suspended %d\n", current_pid);
        setpgid(shell->shell_pgid, shell->shell_pgid);
        tcsetpgrp(STDIN_FILENO, shell->shell_pgid);
        shell->stopped_pid = 0;
        shell->stopped_pid = current_pid;
        if (get_job_from_pid(current_pid, shell) == NULL) {
            add_job(current_pid, shell, shell->last_cmd);
        }
    }
}

void signal_child(int pid, int signal, shell_info_t *my_shell)
{
    static int current_pid = 0;
    static shell_info_t *shell;

    if (my_shell != NULL)
        shell = my_shell;
    if (pid != -1) {
        current_pid = pid;
        return;
    }
    signal_child_suspend(signal, current_pid, shell);
    if (shell->shell_pgid != current_pid) {
        kill(-current_pid, signal);
    }
    if (shell->shell_pgid == current_pid) {
        write(0, "\n", 1);
        disp_actual_dir(NULL);
    }
}

void sig_handler(int signum)
{
    (void)signum;
    signal_child(-1, SIGINT, NULL);
    return;
}

void sigstp_handler(int signum)
{
    (void)signum;
    signal_child(-1, SIGTSTP, NULL);
    return;
}
