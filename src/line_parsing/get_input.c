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

static linked_list_t *get_history_cmd(shell_input_t *user_input,
    linked_list_t *historic, int direction)
{
    if (historic && !historic->next && user_input->input) {
        historic->value = strdup(user_input->input);
        delete_string(user_input);
        insert_string(user_input, historic->value);
    }
    if (direction == UP && historic->prev) {
        historic = historic->prev;
        delete_string(user_input);
        insert_string(user_input, historic->value);
    }
    if (direction == DOWN && historic->next) {
        historic = historic->next;
        delete_string(user_input);
        insert_string(user_input, historic->value);
    }
    return historic;
}

static linked_list_t *move_cursor(shell_input_t *user_input, char direction,
    linked_list_t *historic)
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
        return get_history_cmd(user_input, historic, UP);
    }
    if (direction == 'B') {
        return get_history_cmd(user_input, historic, DOWN);
    }
    return historic;
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

static void check_opening_char(shell_input_t *user_input, char c,
    linked_list_t *historic)
{
    if (c == '"' || c == '(' || c == '\'' || c == '`') {
        if (c == '(')
            insert_char(user_input, ')');
        else
            insert_char(user_input, c);
        move_cursor(user_input, 'D', historic);
    }
}

static void check_input(shell_input_t *user_input, char c,
    shell_info_t *my_shell, linked_list_t *historic)
{
    if (c == '\t') {
        auto_complete(user_input, my_shell);
    }
    if (!user_input->input && c != '\t') {
        user_input->input = malloc(sizeof(char) * MAX_LENGTH);
        user_input->input[0] = '\0';
    }
    check_opening_char(user_input, c, historic);
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

char *get_prompt(shell_info_t *my_shell)
{
    shell_input_t user_input = {0, 0, NULL};
    char c = 0;
    struct termios initial_settings = init_shell_settings();
    linked_list_t *historic = get_array_from_prev_cmd(strdup(""));

    c = getchar();
    while (c != '\n' && c != EOT) {
        if (c == ESC) {
            getchar();
            historic = move_cursor(&user_input, getchar(), historic);
        } else {
            check_input(&user_input, c, my_shell, historic);
        }
        c = getchar();
    }
    return finish_input(&user_input, &initial_settings, c);
}
