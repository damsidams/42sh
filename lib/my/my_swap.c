/*
** EPITECH PROJECT, 2023
** MY_SWAP
** File description:
** Write a function that swaps the content of two integers
*/

void my_swap(int *a, int *b)
{
    int stock;

    stock = *b;
    *b = *a;
    *a = stock;
}
