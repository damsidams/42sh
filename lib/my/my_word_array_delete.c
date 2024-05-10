/*
** EPITECH PROJECT, 2024
** LIB
** File description:
** Delete an element in
** a word array
*/
#include <stdlib.h>
#include "my.h"

static int nb_words(char **word_array)
{
    int i = 0;

    for (; word_array[i]; i++) {
    }
    return i;
}

char **my_word_array_delete(char **word_array, char *word)
{
    char **arr = malloc(sizeof(char *) * (nb_words(word_array)));
    int len = my_strlen(word);
    int j = 0;

    for (int i = 0; word_array[i]; i++) {
        if (my_strncmp(word_array[i], word, len) != 0) {
            arr[j] = my_strdup(word_array[i]);
            j++;
        }
    }
    arr[j] = NULL;
    free_str_array(word_array);
    return arr;
}
