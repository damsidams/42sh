/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** Function for built in cmd
*/

#include <stddef.h>
#include "shell.h"

bool built_in_command(char **args, shell_info_t *my_shell)
{
    char *flags_array[] =
        {"env", "cd", "setenv", "unsetenv", "color", "history", "alias", NULL};
    void (*fptr_array[])() =
        {disp_env, change_dir, set_env, unset_env, set_color
        , display_historic, my_alias};

    if (args[0] == NULL)
        return false;
    for (int i = 0; flags_array[i]; i++) {
        if (flags_array[i] == NULL)
            break;
        if (my_strcmp(flags_array[i], args[0]) == 0){
            fptr_array[i](args, my_shell);
            return true;
        }
    }
    return false;
}
