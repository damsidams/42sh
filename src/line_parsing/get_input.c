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

static void move_cursor(shell_input_t *user_input, char direction)
{
    if (direction == 'D' && user_input->cursor > 0) {
        printf("%s", MOVE_LEFT);
        user_input->cursor--;
    }
    if (direction == 'C' && user_input->cursor < user_input->index) {
        user_input->cursor++;
        printf("%s", MOVE_RIGHT);
    }
    if (direction == 'A') {
        printf("history not implemented\n");
    }
    if (direction == 'B') {
        printf("history not implemented\n");
    }
}

static void delete_char(shell_input_t *user_input)
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

static void insert_char(shell_input_t *user_input, char c)
{
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

static void check_opening_char(shell_input_t *user_input, char c)
{
    if (c == '"' || c == '(' || c == '\'' || c == '`') {
        if (c == '(')
            insert_char(user_input, ')');
        else
            insert_char(user_input, c);
        move_cursor(user_input, 'D');
    }
}

static void check_input(shell_input_t *user_input, char c,
    shell_info_t *my_shell)
{
    if (c == '\t') {
        auto_complete(user_input, my_shell);
    }
    if (!user_input->input && c != '\t') {
        user_input->input = malloc(sizeof(char) * MAX_LENGTH);
        user_input->input[0] = '\0';
    }
    check_opening_char(user_input, c);
    if (c == DEL || c == '\b') {
        delete_char(user_input);
    } else if (c != DEL && c != '\b' && c != '\t'){
        insert_char(user_input, c);
    }
}

static char *finish_input(shell_input_t *user_input,
    struct termios *initial_settings, char last_char)
{
    tcsetattr(STDIN_FILENO, TCSANOW, initial_settings);
    if (last_char == EOT)
        return "EOT";
    return user_input->input;
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

char *get_prompt(shell_info_t *my_shell)
{
    shell_input_t user_input = {0, 0, NULL};
    char c;
    struct termios initial_settings = init_shell_settings();

    c = getchar();
    while (c != '\n' && c != EOT) {
        if (c == ESC) {
            getchar();
            move_cursor(&user_input, getchar());
        } else {
            check_input(&user_input, c, my_shell);
        }
        c = getchar();
    }
    return finish_input(&user_input, &initial_settings, c);
}
