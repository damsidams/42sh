/*
** EPITECH PROJECT, 2023
** MY_SORT_INT_ARRAY
** File description:
** Write a function that sorts an integer array in ascending order
*/

static void my_swapnbr(int *a, int *b)
{
    int stock;

    stock = *b;
    *b = *a;
    *a = stock;
}

static void ismore(int a, int b, int *array)
{
    if (array[a] > array[b])
        my_swapnbr(&(array[a]), &(array[b]));
}

void my_sort_int_array(int *array, int size)
{
    int max = size;
    int a = 0;
    int b = 1;

    while (max > 0) {
        while (b < max) {
            ismore(a, b, array);
            a++;
            b++;
        }
        a = 0;
        b = 1;
        max--;
    }
}
