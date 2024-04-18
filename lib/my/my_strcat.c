/*
** EPITECH PROJECT, 2023
** my_strcat temp
** File description:
** bhkto-kgrthl-oh-toktjhikuoh
*/

#include "my.h"
#include <stdlib.h>
#include <stddef.h>

char *my_strcat(char const *str, char const *to_add)
{
    int dest_size = my_strlen(str) + my_strlen(to_add);
    char *dest = malloc(sizeof(char) * (dest_size + 1));
    int i_dest = 0;
    int i_str = 0;

    if (my_strlen(str) == 0 || my_strlen(to_add) == 0) {
        return NULL;
    }
    while (i_dest < my_strlen(str)) {
        dest[i_dest] = str[i_dest];
        i_dest++;
    }
    while (i_dest < dest_size) {
        dest[i_dest] = to_add[i_str];
        i_dest++;
        i_str++;
    }
    dest[i_dest] = '\0';
    return dest;
}
