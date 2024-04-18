/*
** EPITECH PROJECT, 2023
** MY_COMPUTE_POWER_REC
** File description:
** recursive function that returns the first argument raised to the power
*/

int my_compute_power_rec(int nb, int p)
{
    if (p == 0)
        return 1;
    if (nb > 2147483647)
        return 0;
    if (p == 1)
        return nb;
    if (p < 0)
        return 0;
    if (nb * my_compute_power_rec(nb, p - 1) < 2147483647
        && nb * my_compute_power_rec(nb, p - 1) > -2147483648)
        return nb * my_compute_power_rec(nb, p - 1);
    return 0;
}
