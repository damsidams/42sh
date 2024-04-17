/*
** EPITECH PROJECT, 2023
** MY_STRUPCASE
** File description:
** Write a function that puts every letter of every word in it in uppercase
*/

char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > 96 && str[i] < 123)
            str[i] = str[i] - 32;
    }
    return str;
}
