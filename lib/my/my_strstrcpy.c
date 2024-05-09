/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Function to copy a char ** array to a dest (doesn't add NULL at the end)
** Returns NULL is error else the dest array
*/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "my.h"

char **my_strstrcpy(char **dest, char **src)
{
    for (unsigned int i = 0; src[i] != NULL; i++) {
        dest[i] = malloc(sizeof(char) * my_strlen(src[i]) + 1);
        if (dest[i] == NULL)
            return NULL;
        dest[i] = strcpy(dest[i], src[i]);
    }
    return dest;
}
