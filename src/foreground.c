/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** foreground for the shell processes
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

static void foreground_process_args(char **args, shell_info_t *my_shell)
{
    int process_nb = 0;
    process_t *process = NULL;

    if (args[1][0] == '%') {
        process_nb = my_getnbr(args[1]);
        if (my_shell->stopped_pid != my_shell->shell_pgid) {
            kill(my_shell->stopped_pid, SIGCONT);
            my_shell->stopped_pid = my_shell->shell_pgid;
        }
        if (job_exist(process_nb, my_shell)) {
            process = get_job_from_id(process_nb, my_shell);
            puts(process->cmd);
            setpgid(process->pid, process->pid);
            wait_for_pid(process->pid, my_shell);
            remove_job(process->pid, my_shell);
            return;
        } else {
            puts("fg: No such job.");
        }
    }
}

static bool stopped_basic_fg(process_t *process, bool good,
    shell_info_t *my_shell)
{
    int pid = my_shell->stopped_pid;

    if (pid != my_shell->shell_pgid) {
        printf("stopped fg: %d\n", pid);
        process = get_job_from_pid(pid, my_shell);
        puts(process->cmd);
        setpgid(pid, pid);
        wait_for_pid(pid, my_shell);
        remove_job(pid, my_shell);
        my_shell->stopped_pid = my_shell->shell_pgid;
        good = true;
    }
    return good;
}

static void basic_fg(shell_info_t *my_shell)
{
    process_t *process = NULL;
    int good = false;
    int wstatus = 0;
    int pid = my_shell->jobs->pid;

    if (my_shell->stopped_pid != my_shell->shell_pgid)
        kill(my_shell->stopped_pid, SIGCONT);
    good = stopped_basic_fg(process, good, my_shell);
    if (my_shell->jobs && !good) {
        printf("last fg: %d\n", pid);
        puts(my_shell->jobs->cmd);
        setpgid(pid, pid);
        wait_for_pid(pid, my_shell);
        remove_job(pid, my_shell);
        check_seg_fault(wstatus, my_shell);
        good = true;
    }
    if (!good){
        puts("fg: No current job.");
    }
}

void foreground_process(char **args, shell_info_t *my_shell)
{
    int len = my_strstrlen(args);

    if (len == 1) {
        basic_fg(my_shell);
    }
    if (len == 2) {
        foreground_process_args(args, my_shell);
    }
}
