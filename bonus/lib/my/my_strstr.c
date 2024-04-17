/*
** EPITECH PROJECT, 2023
** TASK 05
** File description:
** Reproduce the behavior of the strstr function
*/

static char *oncefound(char *str, char const *to_find, int j, int suite)
{
    int debut = j;

    while (str[j] == to_find[suite]) {
        if (to_find[suite + 1] == '\0')
            return str + debut;
        suite += 1;
        j += 1;
    }
    return 0;
}

char *my_strstr(char *str, char const *to_find)
{
    int suite;
    int j;
    char *rep = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_find[0] && rep == 0) {
            suite = 0;
            j = i;
            rep = oncefound(str, to_find, j, suite);
        }
    }
    return rep;
}
