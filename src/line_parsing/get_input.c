/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-nicolas.nunney
** File description:
** get_input.c
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include "shell.h"

static void move_cursor(int *cursor, int max_index, char direction)
{
    if (direction == 'D' && *cursor > 0) {
        printf("\033[1D");
        (*cursor)--;
    } else if (direction == 'C' && *cursor < max_index) {
        (*cursor)++;
        printf("\033[1C");
    }
}

static void delete_char(int *index, int *cursor, char *phrase)
{
    if (*index > 0 && *cursor > 0) {
        memmove(&phrase[*cursor - 1], &phrase[*cursor], *index - *cursor + 1);
        (*index)--;
        (*cursor)--;
        printf("\033[D\033[P");
        for (int i = *cursor; i < *index; i++) {
            printf("%c", phrase[i]);
        }
        printf(" ");
        for (int i = *index + 1; i > *cursor; i--) {
            printf("\033[1D");
        }
    }
}

static void insert_char(int *index, int *cursor, char *phrase, char c)
{
    if (*index < MAX_LENGTH - 1) {
        memmove(&phrase[*cursor + 1], &phrase[*cursor], *index - *cursor + 1);
        phrase[*cursor] = c;
        (*index)++;
        (*cursor)++;
        printf("%c", c);
        for (int i = *cursor; i < *index; i++) {
            printf("%c", phrase[i]);
        }
        for (int i = *index; i > *cursor; i--) {
            printf("\033[1D");
        }
    }
}

static struct termios init_shell_settings(void)
{
    struct termios new_settings;
    struct termios initial_settings;

    tcgetattr(STDIN_FILENO, &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_settings) != 0) {
        exit(EXIT_FAILURE);
    }
    fflush(stdout);
    return initial_settings;
}

static void check_input(int *index, int *cursor, char *input, char c)
{
    if (c == '\t')
        return;
    if (c == DEL || c == '\b') {
        delete_char(index, cursor, input);
    } else {
        insert_char(index, cursor, input, c);
    }
}

static char *finish_input(char *input, int index,
    struct termios *initial_settings, char last_char)
{
    input[index] = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, initial_settings);
    if (last_char == EOT)
        return NULL;
    return input;
}

char *get_prompt(void)
{
    char *input = malloc(sizeof(char) * MAX_LENGTH);
    int index = 0;
    int cursor = 0;
    char c;
    struct termios initial_settings = init_shell_settings();

    c = getchar();
    while (c != '\n' && c != EOT) {
        if (c == ESC) {
            getchar();
            move_cursor(&cursor, index, getchar());
        } else {
            check_input(&index, &cursor, input, c);
        }
        c = getchar();
    }
    return finish_input(input, index, &initial_settings, c);
}
