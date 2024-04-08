/*
** EPITECH PROJECT, 2023
** MY_IS_PRIME
** File description:
** Write a function that returns 1 if the number is prime
*/

int my_is_prime(int nb)
{
    int i = nb;
    int j = 2;

    nb = nb / 2;
    if (i == 1)
        return 0;
    if (i < 0)
        return 0;
    while (j < nb) {
        if ((i % j) == 0)
            return 0;
        j++;
    }
    return 1;
}
