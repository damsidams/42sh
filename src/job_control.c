/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** job control for the shell
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

void end_job_control(shell_info_t *my_shell)
{
    process_t *next = NULL;

    if (my_shell->last_cmd)
        free(my_shell->last_cmd);
    for (process_t *i = my_shell->jobs; i;) {
        next = i->next;
        if (i->cmd)
            free(i->cmd);
        free(i);
        i = next;
    }
}
