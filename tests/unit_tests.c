/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** unit_tests.c
*/

#include "../include/shell.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(unit_test, get_file_size)
{
    cr_assert_eq(get_file_size("src/main.c"), 263);
    cr_assert_eq(get_file_size("not existing file"), OPEN_ERROR);
}

Test(unit_test, open_append)
{
    open_append("test_file");
}

Test(unit_test, read_open)
{
    read_open("unknow file");
}
