/*
** EPITECH PROJECT, 2023
** SETTING_UP
** File description:
** Return an array of lines extracted for the array given as an argument
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "my.h"

static bool in_delim(char c, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (c == delim[i])
            return true;
    }
    return false;
}

static int get_nb_lines(char *buf, char *delim)
{
    int cpt = 0;

    if (buf != NULL && buf[0] != '\0')
        cpt = 1;
    for (int i = 0; buf[i] != '\0'; i++) {
        if (in_delim(buf[i], delim)) {
            cpt++;
        }
    }
    return cpt;
}

static int get_nb_col(char *buf, char *delim)
{
    int i = 0;
    int cpt = 0;
    int final_size = 0;

    while (buf[i] != '\0') {
        while (!in_delim(buf[i], delim) && buf[i] != '\0') {
            cpt++;
            i++;
        }
        if (cpt > final_size)
            final_size = cpt;
        cpt = 0;
        if (buf[i] != '\0')
            i++;
    }
    return final_size;
}

void check_comment(char *buf, int *i)
{
    if ((buf[*i] == '#' && buf[*i + 1] == '#') || (buf[*i] == '#' &&
        *i >= 0 && buf[*i - 1] == '#'))
        return;
    if (buf[*i] == '#') {
        while (buf[*i] != '\0' && buf[*i] != '\n')
            (*i)++;
    }
}

static bool skip_delim(char *buf, int *i, char *delim)
{
    if (buf[(*i) + 1] != '\0')
        (*i)++;
    check_comment(buf, i);
    if (!in_delim(buf[*i], delim))
        return true;
    return false;
}

static void new_line(char **args, int *index, int nb_col)
{
    args[index[0]][index[1]] = '\0';
    index[1] = 0;
    index[0]++;
    args[index[0]] = malloc(sizeof(char) * nb_col + 10);
}

static int *init_index(void)
{
    int *index = malloc(sizeof(int) * 2);

    index[0] = 0;
    index[1] = 0;
    return index;
}

static char **finish_str_array(int *index, char **args)
{
    char **final_array = NULL;

    if (index[1] > 0) {
        args[index[0]][index[1]] = '\0';
        index[0]++;
    }
    args[index[0]] = NULL;
    final_array = my_str_array_dup_ban_str(args, "\n");
    free(index);
    return final_array;
}

static void add_char(char **args, int *index, char new_char)
{
    args[index[0]][index[1]] = new_char;
    index[1]++;
}

char **my_str_to_word_array(char *buf, char *delim)
{
    char **args = malloc(sizeof(char *) * (get_nb_lines(buf, delim) + 1));
    int *index = init_index();
    int nb_col = get_nb_col(buf, delim);
    bool add_line = false;

    args[index[0]] = malloc(sizeof(char) * nb_col + 1);
    for (int i = 0; buf[i] != '\0'; i++){
        check_comment(buf, &i);
        if (!in_delim(buf[i], delim))
            add_line = true;
        if (buf[i] != '\0' && in_delim(buf[i], delim) && add_line) {
            new_line(args, index, nb_col);
            add_line = skip_delim(buf, &i, delim);
        }
        if (buf[i] != '\0' && !in_delim(buf[i], delim))
            add_char(args, index, buf[i]);
    }
    return finish_str_array(index, args);
}
