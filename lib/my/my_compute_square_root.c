/*
** EPITECH PROJECT, 2023
** MY_COMPUTE_SQUARE_ROOT
** File description:
** function that returns the square root
*/

int my_compute_square_root(int nb)
{
    int i = 1;
    int p = 0;

    while (nb > 0) {
        nb = nb - i;
        i += 2;
        p += 1;
    }
    if (nb == 0)
        return p;
    return 0;
}
