/*
** EPITECH PROJECT, 2023
** MY LIB
** File description:
** Returns the size of the given number given as an int
*/

static int print_neg(int nb, int *size)
{
    if (nb < 0) {
        *size = 1;
        nb *= -1;
    }
    return nb;
}

static int print_nb(int nb, int *size)
{
    if (nb / 10 > 0)
        print_nb(nb / 10, size);
    *size += 1;
    return 0;
}

int my_getnbr_size(int nb)
{
    int size = 0;

    nb = print_neg(nb, &size);
    print_nb(nb, &size);
    return size;
}
