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

static bool new_line(char **args, int *index, int *i, int nb_col, char *buf)
{
    args[index[0]][index[1]] = '\0';
    index[1] = 0;
    index[0]++;
    args[index[0]] = malloc(sizeof(char) * nb_col + 1);
    if (buf[(*i) + 1] != '\0')
        (*i)++;
    return false;
}

static int *init_index(void)
{
    int *index = malloc(sizeof(int) * 2);

    index[0] = 0;
    index[1] = 0;
    return index;
}

static void finish_str_array(int *index, char **args)
{
    if (index[1] > 0) {
        args[index[0]][index[1]] = '\0';
        index[0]++;
    }
    args[index[0]] = NULL;
}

static int get_nb_words(char *str, char *sep)
{
    char *seps = my_strcat(sep, "\t");
    char *token = strtok(str, seps);
    int len = 0;

    while (token) {
        len++;
        token = strtok(NULL, seps);
    }
    free(seps);
    return len;
}

char **my_strtok_to_word_array(char *str_buf, char *sep)
{
    char *temp = my_strdup(str_buf);
    int len = get_nb_words(temp, sep);
    char **array = malloc(sizeof(char *) * (len + 1));
    char *token = strtok(str_buf, sep);
    int count = 0;

    while (token && count != len) {
        array[count] = my_strdup(token);
        count++;
        token = strtok(NULL, sep);
    }
    array[count] = NULL;
    free(temp);
    return array;
}

char **my_str_to_word_array(char *buf, char *delim)
{
    char **args = malloc(sizeof(char *) * (get_nb_lines(buf, delim) + 1));
    int *index = init_index();
    int nb_col = get_nb_col(buf, delim);
    bool add_line = false;

    args[index[0]] = malloc(sizeof(char) * nb_col + 1);
    for (int i = 0; buf[i] != '\0'; i++){
        if (!in_delim(buf[i], delim))
            add_line = true;
        if (buf[i] != '\0' && in_delim(buf[i], delim) && add_line)
            add_line = new_line(args, index, &i, nb_col, buf);
        if (buf[i] != '\0' && !in_delim(buf[i], delim)) {
            args[index[0]][index[1]] = buf[i];
            index[1]++;
        }
    }
    finish_str_array(index, args);
    return args;
}
