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
        printf("%s", MOVE_LEFT);
        (*cursor)--;
    }
    if (direction == 'C' && *cursor < max_index) {
        (*cursor)++;
        printf("%s", MOVE_RIGHT);
    }
    if (direction == 'A') {
        printf("history not implemented\n");
    }
    if (direction == 'B') {
        printf("history not implemented\n");
    }
}

static void delete_char(int *index, int *cursor, char *input)
{
    if (*index > 0 && *cursor > 0) {
        memmove(&input[*cursor - 1], &input[*cursor], *index - *cursor + 1);
        (*index)--;
        (*cursor)--;
        printf("\033[D\033[P");
        for (int i = *cursor; i < *index; i++) {
            printf("%c", input[i]);
        }
        putchar(' ');
        for (int i = *index + 1; i > *cursor; i--) {
            printf("%s", MOVE_LEFT);
        }
    }
}

void insert_char(int *index, int *cursor, char *input, char c)
{
    if (*index < MAX_LENGTH - 1) {
        memmove(&input[*cursor + 1], &input[*cursor], *index - *cursor + 1);
        input[*cursor] = c;
        (*index)++;
        (*cursor)++;
        putchar(c);
        for (int i = *cursor; i < *index; i++) {
            putchar(input[i]);
        }
        for (int i = *index; i > *cursor; i--) {
            printf("%s", MOVE_LEFT);
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

static void check_opening_char(int *index, int *cursor, char *input, char c)
{
    if (c == '"' || c == '(' || c == '\'' || c == '`') {
        if (c == '(')
            insert_char(index, cursor, input, ')');
        else
            insert_char(index, cursor, input, c);
        move_cursor(cursor, *index, 'D');
    }
}

static void check_input(int *index, int *cursor, char *input, char c)
{
    if (c == '\t')
        return;
    check_opening_char(index, cursor, input, c);
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
