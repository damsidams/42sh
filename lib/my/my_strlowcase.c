/*
** EPITECH PROJECT, 2023
** MY_STRLOWCASE
** File description:
** Write a function that puts every letter
** of every word in it in lowercase
*/

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > 65 && str[i] < 91)
            str[i] = str[i] + 32;
    }
    return str;
}
