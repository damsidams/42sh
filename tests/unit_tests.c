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

/* color*/

Test(unit_test, valid_color)
{
    cr_assert_eq(valid_color("red"), 31);
    cr_assert_eq(valid_color("blue"), 34);
    cr_assert_eq(valid_color("yellow"), 33);
    cr_assert_eq(valid_color("magenta"),35);
    cr_assert_eq(valid_color("not a color"), -1);
}

Test(unit_test, set_color)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = malloc(sizeof(char *) * 4);
    
    args[0] = strdup("color");
    args[1] = strdup("blue");
    args[2] = strdup("yellow");
    args[3] = NULL;
    command_handling(my_shell, args);
    cr_assert_eq(my_shell->color[0], 34);
    cr_assert_eq(my_shell->color[1], 33);
}

/* historic */

Test(unit_test, disp_historic)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    char **args = malloc(sizeof(char *) * 4);
    
    args[0] = strdup("color");
    args[1] = strdup("blue");
    args[2] = strdup("yellow");
    args[3] = NULL;
    command_handling(my_shell, args);
    cr_assert_eq(my_shell->exit_status, SUCCESS);
}

Test(unit_test, add_to_save)
{
    cr_assert_eq(add_command_to_save("ls"), SUCCESS);
    cr_assert_eq(add_command_to_save("history"), SUCCESS);
    cr_assert_eq(add_command_to_save("egregt"), SUCCESS);
    cr_assert_eq(add_command_to_save("test"), SUCCESS);
    cr_assert_eq(add_command_to_save("echo something"), SUCCESS);
    cr_assert_eq(add_command_to_save(""), SUCCESS);
}

Test(unit_test, get_array_from_prev_cmd)
{
    cr_assert_not_null(get_array_from_prev_cmd(strdup("")));
    cr_assert_not_null(get_array_from_prev_cmd(strdup("echo pop")));
    cr_assert_not_null(get_array_from_prev_cmd(strdup("history")));
    cr_assert_not_null(get_array_from_prev_cmd(NULL));
}

Test(unit_test, special_get_nbr)
{
    cr_assert_eq(my_special_getnbr("e124to"), 124);
    cr_assert_eq(my_special_getnbr("124to"), 124);
    cr_assert_eq(my_special_getnbr("-e124to"), 124);
    cr_assert_eq(my_special_getnbr("e-1to"), -1);
    cr_assert_eq(my_special_getnbr("eto"), 0);
}

Test(unit_test, read_history)
{
    cr_assert_eq(read_history("zojr"), SYS_ERROR);
}

Test(unit_test, check_if_cmd_needs_to_be_replaced)
{
    char **env = create_strstr("PATH=~/delivery/Project/42sh", "HOST=nicolo", "test=ops", "NB=lo");
    shell_info_t *my_shell = init_shell_info_t(env);
    
    cr_assert_str_eq(check_if_historic(strdup("ls -l"), my_shell), "ls -l");
    cr_assert_str_eq(check_if_historic(strdup("ls -la"), my_shell), "ls -la");
    cr_assert_str_neq(check_if_historic(strdup("!!"), my_shell), "!!");
}
