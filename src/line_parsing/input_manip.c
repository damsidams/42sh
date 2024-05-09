/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
** File description:
** input_manip.c
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include "shell.h"

void delete_char(shell_input_t *user_input)
{
    if (user_input->index > 0 && user_input->cursor > 0) {
        memmove(&(user_input->input[user_input->cursor - 1]),
            &(user_input->input[user_input->cursor]),
            user_input->index - user_input->cursor + 1);
        user_input->index--;
        user_input->cursor--;
        printf("\033[D\033[P");
        for (int i = user_input->cursor; i < user_input->index; i++) {
            printf("%c", user_input->input[i]);
        }
        putchar(' ');
        for (int i = user_input->index + 1; i > user_input->cursor; i--) {
            printf("%s", MOVE_LEFT);
        }
    }
}

void insert_char(shell_input_t *user_input, char c)
{
    if (!user_input->input && c != '\t') {
        user_input->input = malloc(sizeof(char) * MAX_LENGTH);
        user_input->input[0] = '\0';
    }
    if (user_input->index < MAX_LENGTH - 1) {
        memmove(&(user_input->input[user_input->cursor + 1]),
            &(user_input->input[user_input->cursor]),
            user_input->index - user_input->cursor + 1);
        user_input->input[user_input->cursor] = c;
        user_input->index++;
        user_input->cursor++;
        putchar(c);
        for (int i = user_input->cursor; i < user_input->index; i++) {
            putchar(user_input->input[i]);
        }
        for (int i = user_input->index; i > user_input->cursor; i--) {
            printf("%s", MOVE_LEFT);
        }
    }
}

void insert_string(shell_input_t *user_input, char *to_insert)
{
    for (int i = 0; to_insert[i] != '\0'; i++) {
        insert_char(user_input, to_insert[i]);
    }
}

void delete_string(shell_input_t *user_input)
{
    while (my_strlen(user_input->input) != 0) {
        delete_char(user_input);
    }
}
