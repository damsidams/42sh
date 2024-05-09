/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Functions related to test needs
*/

#include <stdlib.h>
#include <string.h>

char **create_strstr(char *s1, char *s2, char *s3, char *s4)
{
    char **strstr = calloc(5, sizeof(char *));

    if (s1)
        strstr[0] = strdup(s1);
    if (s2)
        strstr[1] = strdup(s2);
    if (s3)
        strstr[2] = strdup(s3);
    if (s4)
        strstr[3] = strdup(s4);
    return strstr;
}
