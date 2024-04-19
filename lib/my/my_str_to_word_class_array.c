/*
** EPITECH PROJECT, 2024
** LIB
** File description:
** strtok with cutom delimiters and exceptions
*/

#include <stdlib.h>
#include <stddef.h>
#include "my.h"

static int is_delim(char c, char *delim)
{
    for (int i = 0; delim[i]; i++) {
        if (c == delim[i])
            return 1;
    }
    return 0;
}

static int is_exception(char c)
{
    return (c == '\"' || c == '`');
}

static int get_word_nb(char *str, char *delim)
{
    int word_nb = 0;
    int in_exception = OUT;
    int word_start = 0;
    int last_start = -1;

    for (int i = 0; str[i]; i++) {
        if ((is_delim(str[i], delim) && i > 0 && !is_delim
            (str[i - 1], delim) && in_exception == OUT) || (str[i + 1] == '\0'
            && last_start != word_start)) {
            word_nb++;
            last_start = word_start;
        }
        if (!is_delim(str[i], delim) && i > 0 &&
            is_delim(str[i - 1], delim) && in_exception == OUT)
            last_start = i;
        if (is_exception(str[i]))
            in_exception *= -1;
    }
    return word_nb;
}

static int my_new_word_size(char *str, char *delim)
{
    int i = 0;
    int in_exception = OUT;

    while (str[i] && (!is_delim(str[i], delim) || in_exception == IN)) {
        if (is_exception(str[i]))
            in_exception *= -1;
        i++;
    }
    return i;
}

static void remove_exception(char **str)
{
    char *new_str = NULL;
    int len = my_strlen(*str);
    unsigned int new_index = 0;

    if (is_exception((*str)[len - 1])) {
        new_str = malloc(sizeof(char) * len - 1);
        for (int i = 1; i < len - 1; i++) {
            new_str[new_index] = (*str)[i];
            new_index++;
        }
    } else {
        new_str = malloc(sizeof(char) * len);
        for (int i = 1; i < len; i++) {
            new_str[new_index] = (*str)[i];
            new_index++;
        }
    }
    new_str[new_index] = '\0';
    free(*str);
    *str = new_str;
}

static char *new_word(char *str, int start, char *delim)
{
    char *new_word = malloc(sizeof(char) *
        (my_new_word_size(str + start, delim) + 1));
    int i = start;
    int inew = 0;
    int in_exception = OUT;

    while (str[i] && (!is_delim(str[i], delim) || in_exception == IN)) {
        new_word[inew] = str[i];
        if (is_exception(str[i]))
            in_exception *= -1;
        i++;
        inew++;
    }
    new_word[inew] = '\0';
    if (is_exception(new_word[0]) && new_word[0] != '`')
        remove_exception(&new_word);
    return new_word;
}

static void assist_func(char *str, int i, int *in_exception)
{
    if (is_exception(str[i]))
            *in_exception *= -1;
}

static void second_assist(int *wc, int *last_start, int *word_start)
{
    *wc += 1;
    *last_start = *word_start;
}

char **my_pimp_str_to_wa(char *str, char *delim)
{
    char **array = malloc(sizeof(char *) * (get_word_nb(str, delim) + 1));
    int wc = 0;
    int word_start = 0;
    int last_start = -1;
    int in_exception = OUT;

    for (int i = 0; str[i]; i++) {
        if ((is_delim(str[i], delim) && i > 0 && !is_delim(str[i - 1], delim)
            && in_exception == OUT) || (str[i + 1] == '\0' &&
            last_start != word_start)) {
            array[wc] = new_word(str, word_start, delim);
            second_assist(&wc, &last_start, &word_start);
        }
        if (!is_delim(str[i], delim) && i > 0 &&
            is_delim(str[i - 1], delim) && in_exception == OUT)
            word_start = i;
        assist_func(str, i, &in_exception);
    }
    array[wc] = NULL;
    return array;
}
