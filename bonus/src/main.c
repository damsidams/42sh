/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** main.c
*/

#include "shell.h"

int main(int argc, char **argv, char **env)
{
    (void)argv;
    if (argc != 1) {
        return ERROR_EXIT;
    }
    return my_sh(env);
}
