/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
** File description:
** set_color.c
*/

#include <unistd.h>
#include "struct.h"
#include "my.h"
#include "shell.h"

void disp_color_help(void)
{
    mini_printf("---------COLOR---------\n\n");
    mini_printf("------DESCRIPTION------\n");
    mini_printf("Set the colors of the current directory ");
    mini_printf("displayed in the shell\n\n");
    mini_printf("------HOW TO USE------\n");
    mini_printf("color [SUCCESS_COLOR] [ERROR_COLOR]");
    mini_printf(" -> changes success and error colors\n");
    mini_printf("color -s [SUCCESS_COLOR] -> change success color\n");
    mini_printf("color -e [ERROR_COLOR] -> change error color\n");
    mini_printf("color -d -> reset default colors\n");
    mini_printf("------AVAILABLE COLORS------\n");
    mini_printf("black\nred\ngreen\nyellow\n");
    mini_printf("blue\nmagenta\ncyan\nwhite\n");
}

int valid_color(char *color)
{
    char *valid_colors[] = {
        "black",
        "red",
        "green",
        "yellow",
        "blue",
        "magenta",
        "cyan",
        "white",
        NULL};
    int converted_colors[] = {30, 31, 32, 33, 34, 35, 36, 37};

    for (int i = 0; valid_colors[i]; i++) {
        if (my_strcmp(color, valid_colors[i]) == 0)
            return converted_colors[i];
    }
    return -1;
}

static void change_all_colors(char **args, shell_info *my_shell)
{
    int success_color = valid_color(args[1]);
    int error_color = valid_color(args[2]);

    if (success_color == -1 || error_color == -1) {
        my_putstr_err("mysh: color: bad arguments\n");
        my_putstr_err("try color -h to see options\n");
        my_shell->exit_status = 1;
    } else {
        my_shell->color[0] = success_color;
        my_shell->color[1] = error_color;
        my_shell->exit_status = 0;
    }
}

static void change_success(char **args, shell_info *my_shell)
{
    int success_color = valid_color(args[2]);

    if (success_color == -1) {
        my_putstr_err("mysh: color: bad arguments\n");
        my_putstr_err("try color -h to see options\n");
        my_shell->exit_status = 1;
    } else {
        my_shell->color[0] = success_color;
        my_shell->exit_status = 0;
    }
}

static void change_error(char **args, shell_info *my_shell)
{
    int error_color = valid_color(args[2]);

    if (error_color == -1) {
        my_putstr_err("mysh: color: bad arguments\n");
        my_putstr_err("try color -h to see options\n");
        my_shell->exit_status = 1;
    } else {
        my_shell->color[1] = error_color;
        my_shell->exit_status = 0;
    }
}

static void reset_def(char **args, shell_info *my_shell)
{
    (void)args;
    my_shell->color[0] = valid_color(DEFAULT_SUCCESS_COLOR);
    my_shell->color[1] = valid_color(DEFAULT_ERROR_COLOR);
    my_shell->exit_status = 0;
}

void get_options(char **args, shell_info *my_shell)
{
    char *flags[] = {"-s", "-e", "-r", NULL};
    void (*fptr_array[])() = {change_success, change_error, reset_def, NULL};

    for (int i = 0; flags[i]; i++) {
        if (my_strcmp(args[1], flags[i]) == 0) {
            fptr_array[i](args, my_shell);
            return;
        }
    }
    if (args[1][0] != '-')
        change_all_colors(args, my_shell);
    else {
        my_putstr_err("mysh: color: bad arguments\n");
        my_putstr_err("try color -h to see options\n");
        my_shell->exit_status = 1;
    }
}

void set_color(char **args, shell_info *my_shell)
{
    if (my_strstrlen(args) == 2 && my_strcmp(args[1], "-h") == 0) {
        disp_color_help();
        my_shell->exit_status = 0;
        return;
    }
    if (my_strstrlen(args) <= 2) {
        my_putstr_err("mysh: colors not enough arguments:\n");
        my_putstr_err("try color -h to see options\n");
        my_shell->exit_status = 1;
        return;
    }
    if (my_strstrlen(args) > 3) {
        my_putstr_err("too many arguments:\n");
        my_putstr_err("try color -h to see options\n");
        my_shell->exit_status = 1;
        return;
    }
    get_options(args, my_shell);
}
