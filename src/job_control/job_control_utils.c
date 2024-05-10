/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** job control utillity functions
*/
#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "struct.h"

bool job_exist(int process_nb, shell_info_t *my_shell)
{
    for (process_t *temp = my_shell->jobs; temp; temp = temp->next) {
        if (process_nb == temp->nb)
            return true;
        temp = temp->next;
    }
    return false;
}

void wait_for_pid(int pid, shell_info_t *my_shell)
{
    int wstatus = 0;

    signal_child(pid, 0, NULL);
    tcsetpgrp(STDIN_FILENO, -pid);
    waitpid(pid, &wstatus, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, my_shell->shell_pgid);
    check_seg_fault(wstatus, my_shell);
}

process_t *get_job_from_pid(int pid, shell_info_t *my_shell)
{
    for (process_t *temp = my_shell->jobs; temp; temp = temp->next) {
        if (temp->pid == pid)
            return temp;
    }
    return NULL;
}

process_t *get_job_from_id(int nb, shell_info_t *my_shell)
{
    for (process_t *temp = my_shell->jobs; temp; temp = temp->next) {
        if (temp->nb == nb)
            return temp;
    }
    return NULL;
}
