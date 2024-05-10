/*
** EPITECH PROJECT, 2024
** LIB
** File description:
** my_str_append
*/
#include <stdlib.h>
#include "my.h"

char *my_str_append(char *dst, char *src)
{
    int len = my_strlen(dst) + my_strlen(src);
    char *word = malloc(sizeof(char) * (len + 1));
    int idx = 0;

    for (int i = 0; dst[i] != '\0'; i++) {
        word[idx] = dst[i];
        idx++;
    }
    for (int i = 0; src[i] != '\0'; i++) {
        word[idx] = src[i];
        idx++;
    }
    word[idx] = '\0';
    free(dst);
    return word;
}
