/*
** EPITECH PROJECT, 2023
** MY_STRNCPY
** File description:
** Write a function that copies n characters from a string into another
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int fincopie;

    if (src[0] == '\0') {
        dest[0] = '\n';
        return dest;
    }
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        fincopie = i + 1;
    }
    dest[fincopie] = '\0';
    return dest;
}
