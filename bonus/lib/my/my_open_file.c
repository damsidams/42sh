/*
** EPITECH PROJECT, 2023
** MY_LIB
** File description:
** Open a file and return the filedescriptor
*/

#include "my.h"
#include <fcntl.h>

int fs_open_file(char const *filePath)
{
    int fd = open(filePath, O_RDONLY);

    if (fd < 0) {
        my_putstr_err("The file doesn't exist or couldn't be opened\n");
        return -1;
    }
    return fd;
}
