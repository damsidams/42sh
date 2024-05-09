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
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "struct.h"

process_t *add_job(int pid, shell_info_t *my_shell, char *cmd)
{
    static int nb_jobs = 0;
    process_t *process = malloc(sizeof(process_t));

    nb_jobs++;
    process->nb = nb_jobs;
    process->pid = pid;
    process->next = my_shell->jobs;
    process->is_background = false;
    if (cmd)
        process->cmd = strdup(cmd);
    my_shell->jobs = process;
    printf("[%d] %d\n", nb_jobs, pid);
    return my_shell->jobs;
}

void remove_job(int pid, shell_info_t *my_shell)
{
    process_t *element = my_shell->jobs;
    process_t *previous = my_shell->jobs;

    if (element != NULL && element->pid == pid) {
        my_shell->jobs = element->next;
        if (element->cmd)
            free(element->cmd);
        free(element);
        return;
    }
    while (element != NULL && element->pid != pid) {
        previous = element;
        element = element->next;
    }
    if (element == NULL)
        return;
    previous->next = element->next;
    if (element->cmd)
        free(element->cmd);
    free(element);
}

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
