/*
** EPITECH PROJECT, 2024
** LIB
** File description:
** strtok with cutom delimiters and exceptions
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include "my.h"

static bool my_str_contains(char *str, char *delim)
{
    unsigned int i = 0;

    while (str[i] && delim[i] && str[i] == delim[i])
        i++;
    if (i == 0 || delim[i] != '\0')
        return false;
    if (delim[i - 1] != str[i - 1])
        return false;
    return true;
}

static int my_ssc(char *str, char **delim)
{
    for (unsigned int i = 0; delim[i]; i++) {
        if (my_str_contains(str, delim[i]))
            return i;
    }
    return -1;
}

static int is_exception(char c)
{
    return (c == '\"');
}

static int get_word_nb(char *str, char **delim)
{
    int word_nb = 0;
    int in_except = OUT;
    int ws = 0;
    int ls = -1;

    for (int i = 0; str[i]; i++) {
        if ((my_ssc(str + i, delim) >= 0 && i > 0 &&
            my_ssc(str + i - 1, delim) < 0 && in_except == OUT)
            || (str[i + 1] == '\0' && ls != ws)) {
            word_nb++;
            ls = ws;
        }
        if (my_ssc(str + i, delim) < 0 && i > 0 &&
            my_ssc(str + i - 1, delim) >= 0 && in_except == OUT)
            ls = i + my_strlen(delim[my_ssc(str + i - 1, delim)]);
        if (is_exception(str[i]))
            in_except *= -1;
    }
    return word_nb;
}

static int my_new_word_size(char *str, char **delim)
{
    int i = 0;
    int in_except = OUT;

    while (str[i] && (my_ssc(str + i, delim) < 0 || in_except == IN)) {
        if (is_exception(str[i]))
            in_except *= -1;
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

static char *new_word(char *str, int start, char **delim)
{
    char *new_word = malloc(sizeof(char) *
        (my_new_word_size(str + start, delim) + 2));
    int i = start;
    int inew = 0;
    int in_except = OUT;

    if (i > 0)
        i--;
    while (str[i] && (my_ssc(str + i, delim) < 0 || in_except == IN)) {
        new_word[inew] = str[i];
        if (is_exception(str[i]))
            in_except *= -1;
        i++;
        inew++;
    }
    new_word[inew] = '\0';
    if (is_exception(new_word[0]))
        remove_exception(&new_word);
    return new_word;
}

static void assist_func(char *str, int i, int *in_except)
{
    if (is_exception(str[i]))
            *in_except *= -1;
}

static void second_assist(int *wc, int *ls, int *ws)
{
    *wc += 1;
    *ls = *ws;
}

char **my_tuned_str_to_wa(char *str, char **delim)
{
    char **array = malloc(sizeof(char *) * (get_word_nb(str, delim) + 1));
    int wc = 0;
    int ws = 0;
    int ls = -1;
    int in_except = OUT;

    for (int i = 0; str[i]; i++) {
        if ((my_ssc(str + i, delim) >= 0 && i > 0 && my_ssc(str + i - 1, delim)
            < 0 && in_except == OUT) || (str[i + 1] == '\0' && ls != ws)) {
            array[wc] = new_word(str, ws, delim);
            second_assist(&wc, &ls, &ws);
        }
        if (my_ssc(str + i, delim) < 0 && i > 0 &&
            my_ssc(str + i - 1, delim) >= 0 && in_except == OUT) {
            ws = i + my_strlen(delim[my_ssc(str + i - 1, delim)]);
        }
        assist_func(str, i, &in_except);
    }
    array[wc] = NULL;
    return array;
}
