/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** none
*/

#include <stddef.h>
#include <stdlib.h>
#include "shell.h"

void display_historic(char **args, shell_info_t *my_shell)
{
    char *buffer = NULL;

    (void)args;
    buffer = get_file_content(HISTORIC_FILENAME);
    if (buffer == NULL || my_strlen(buffer) <= 0) {
        my_shell->exit_status = 1;
        return;
    }
    my_putstr(buffer);
    free(buffer);
    my_shell->exit_status = SUCCESS;
}
