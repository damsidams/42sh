/*
** EPITECH PROJECT, 2024
** unit_tests
** File description:
** function that allow me to test my program
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stddef.h>
#include "../include/shell.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

/* initialisation */

Test(unit_test, set_stuct_with_good_env)
{
    char **env = malloc(sizeof(char) * 3);
    shell_info_t *my_shell = NULL;

    env[0] = my_strdup("PATH=vehifvhu");
    env[1] = my_strdup("HOST=ezfhbvj");
    env[2] = NULL;
    my_shell = init_shell_info_t(env);
    cr_assert_not_null(my_shell);
}

Test(unit_test, set_stuct_with_env_null)
{
    shell_info_t *my_shell = NULL;

    my_shell = init_shell_info_t(NULL);
    cr_assert_not_null(my_shell);
}

/* env */

Test(unit_test, set_env_funcs, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "BAB=ops", "NB=lo");
    char *av[] = {"setenv", NULL};
    char *av2[] = {"setenv", "test", NULL};
    char *av3[] = {"setenv", "test75", "42", NULL};
    char *av4[] = {"setenv", "45test75", "84", NULL};
    shell_info_t *my_shell = NULL;

    my_shell = init_shell_info_t(env);
    set_env(av, my_shell);
    cr_assert_eq(my_shell->exit_status, SUCCESS);
    set_env(av2, my_shell), SUCCESS;
    cr_assert_eq(my_shell->exit_status, SUCCESS);
    set_env(av3, my_shell), SUCCESS;
    cr_assert_eq(my_shell->exit_status, SUCCESS);
    set_env(av4, my_shell), NOT_ALLOWED;
    cr_assert_eq(my_shell->exit_status, NOT_ALLOWED);
    free_str_array(env);
}

Test(unit_test, unset_env_funcs, .init=redirect_all_stdout)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    char *av[] = {"unsetenv", NULL};
    char *av2[] = {"unsetenv", "test", NULL};
    char *av3[] = {"unsetenv", "7test75", NULL};
    shell_info_t *my_shell = init_shell_info_t(env);

    unset_env(av, my_shell);
    cr_assert_eq(my_shell->exit_status, NOT_ALLOWED);
    unset_env(av2, my_shell);
    cr_assert_eq(my_shell->exit_status, SUCCESS);
    unset_env(av3, my_shell);
    cr_assert_eq(my_shell->exit_status, SUCCESS);
    free_str_array(env);
}

Test(unit_test, env_get_name)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");

    cr_assert_str_eq(get_name(env, 2), "test");
}

Test(unit_test, env_get_path)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    char **strstr = get_paths(env);
    char **env2 = create_strstr("NO=noenv", "", "", "");
    char **t2 = get_paths(env2);

    cr_assert_str_eq(strstr[0], "PATH");
    cr_assert_str_eq(strstr[1], "~/delivery/Project/42sh");
    cr_assert_null(t2);
}

/* built in*/

Test(unit_test, change_dir)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = malloc(sizeof(char *) * 3);
    
    args[0] = strdup("cd");
    args[1] = strdup("-");
    args[2] = NULL;
    change_dir(args, my_shell);
    cr_assert_eq(my_shell->exit_status, SUCCESS);
}

/* execution */

Test(unit_test, command_handling)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = malloc(sizeof(char *) * 4);
    
    args[0] = strdup("ls");
    args[1] = strdup(">");
    args[2] = strdup("tmp");
    args[3] = NULL;
    command_handling(my_shell, args);
    cr_assert_eq(my_shell->exit_status, SUCCESS);
    command_handling(my_shell, NULL);
}
