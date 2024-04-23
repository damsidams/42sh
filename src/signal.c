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

void sig_handler(int signum)
{
    (void)signum;
    signal_child(-1, SIGINT, NULL);
    write(0, "\n", 1);
    disp_actual_dir(NULL);
    return;
}

void sigstp_handler(int signum)
{
    (void)signum;
    signal_child(-1, SIGTSTP, NULL);
    write(0, "\n", 1);
    disp_actual_dir(NULL);
    return;
}
