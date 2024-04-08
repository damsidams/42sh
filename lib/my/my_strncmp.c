/*
** EPITECH PROJECT, 2023
** MY_STRNCMP
** File description:
** compare
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1 && i < n - 1)
        i++;
    if ((s1[i] == '\0' && s2[i] == '\0') || s1[i] == s2[i])
        return 0;
    if (s1[i] == '\0')
        return -1;
    if (s2[i] == '\0')
        return 1;
    if (s1[i] > s2[i])
        return 1;
    return -1;
}

int my_strncmp_banned_char(char const *s1, char const *s2, int n,
    char banned_char)
{
    int i = 0;
    int j = 0;

    while (s1[i] == banned_char)
        i++;
    while (s2[j] == banned_char)
        j++;
    while (s1[i] && s2[j] && s1[i] == s2[j] && i < n - 1 && j < n - 1) {
        i++;
        j++;
    }
    if ((s1[i] == '\0' && s2[j] == '\0') || s1[i] == s2[j])
        return 0;
    if (s1[i] == '\0')
        return -1;
    if (s2[j] == '\0')
        return 1;
    if (s1[i] > s2[j])
        return 1;
    return -1;
}
