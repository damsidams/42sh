/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** job control for the shell
*/

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "struct.h"

void add_job(int pid, shell_info_t *my_shell, bool suspended)
{
    static int nb_jobs = 0;

    nb_jobs++;
    my_shell->jobs = realloc(my_shell->jobs,
        sizeof(process_t) * (nb_jobs + 1));
    my_shell->jobs[nb_jobs - 1].nb = nb_jobs;
    my_shell->jobs[nb_jobs - 1].pid = pid;
    my_shell->jobs[nb_jobs] = (process_t){-1, -1};
    if (!suspended) {
        printf("[%d] %d\n", nb_jobs, pid);
    } else {
        puts("Suspended");
    }
}

static bool job_exist(int process_nb, shell_info_t *my_shell)
{
    for (int i = 0; my_shell->jobs[i].nb != -1; i++) {
        if (process_nb == my_shell->jobs[i].nb)
            return true;
    }
    return false;
}

void wait_for_pid(int pid, shell_info_t *my_shell)
{
    int wstatus = 0;

    tcsetpgrp(STDIN_FILENO, pid);
    signal_child(pid, 0, NULL);
    waitpid(-pid, &wstatus, WUNTRACED);
    check_seg_fault(wstatus, my_shell);
    tcsetpgrp(STDIN_FILENO, getpgrp());
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
    if (signal == SIGTSTP) {
        shell->stopped_pid = current_pid;
        tcsetpgrp(STDIN_FILENO, getpgrp());
        setpgid(0, 0);
        add_job(current_pid, shell, true);
    }
    if (getpgrp() != current_pid) {
        kill(-current_pid, signal);
    }
}

static void background_process_args(char **args, shell_info_t *my_shell)
{
    int process_nb = 0;

    if (args[1][0] == '%') {
        process_nb = my_getnbr(args[1]);
        if (job_exist(process_nb, my_shell)) {
            signal_child(my_shell->jobs[process_nb - 1].pid, 0, NULL);
            kill(-my_shell->jobs[process_nb - 1].pid, SIGCONT);
            tcsetpgrp(STDIN_FILENO, getpgrp());
            setpgid(0, 0);
            return;
        } else {
            puts("bg: No such job.");
        }
    }
}

void background_process(char **args, shell_info_t *my_shell)
{
    int len = my_strstrlen(args);

    if (len == 1) {
        signal_child(my_shell->stopped_pid, 0, NULL);
        kill(my_shell->stopped_pid, SIGCONT);
    }
    if (len == 2) {
        background_process_args(args, my_shell);
    }
}

static void foreground_process_args(char **args, shell_info_t *my_shell)
{
    int process_nb = 0;
    int wstatus = 0;

    if (args[1][0] == '%') {
        process_nb = my_getnbr(args[1]);
        if (my_shell->stopped_pid != -1) {
            kill(-my_shell->stopped_pid, SIGCONT);
            my_shell->stopped_pid = -1;
        }
        if (job_exist(process_nb, my_shell)) {
            signal_child(my_shell->jobs[process_nb - 1].pid, 0, NULL);
            tcsetpgrp(STDIN_FILENO, my_shell->jobs[process_nb - 1].pid);
            waitpid(-my_shell->jobs[process_nb - 1].pid, &wstatus, 0);
            check_seg_fault(wstatus, my_shell);
            tcsetpgrp(STDIN_FILENO, getpgrp());
            return;
        } else {
            puts("fg: No such job.");
        }
    }
}

void foreground_process(char **args, shell_info_t *my_shell)
{
    int len = my_strstrlen(args);
    int wstatus = 0;

    if (len == 1) {
        if (my_shell->stopped_pid != -1) {
            signal_child(my_shell->stopped_pid, 0, NULL);
            tcsetpgrp(STDIN_FILENO, my_shell->stopped_pid);
            kill(my_shell->stopped_pid, SIGCONT);
            waitpid(my_shell->stopped_pid, &wstatus, 0);
            check_seg_fault(wstatus, my_shell);
            tcsetpgrp(STDIN_FILENO, getpgrp());
            my_shell->stopped_pid = -1;
        } else {
            puts("fg: No current job.");
        }
    }
    if (len == 2) {
        foreground_process_args(args, my_shell);
    }
}
