/*
** EPITECH PROJECT, 2023
** MY.H
** File description:
** Write your my.h header file that contains the prototypes
** of all the functions exposed by your libmy.a
*/

#ifndef MY_H
    #define MY_H
    #include <stdbool.h>

int my_putchar(char);
int my_putchar_err(char);
int my_isneg(int nb);
int my_put_nbr(int nb);
int my_put_unbr(unsigned int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_putstr_err(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
bool my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int my_strstrlen(char **str);
char **my_str_to_word_array(char *buf, char *delim);
char **my_strtok_to_word_array(char *str_buf, char *sep);
char *my_nb_to_str(int nb);
int fs_open_file(char const *filePath);
int my_getnbr_size(int nb);
int mini_printf(char const *format, ...);
char *my_strdup(char *src);
char **my_str_array_dup(char **array);
char **my_str_array_cpy(char **array, char **array_cpy);
void print_str_array(char **array);
void free_str_array(char **array);
int my_strncmp_banned_char(char const *s1, char const *s2, int n,
    char banned_char);
bool my_char_is_alpha(char c);
char **my_str_array_dup_ban_str(char **array, char *str);
void free_triple_array(char ***array);
void my_free_n_str(int nb_of_str, ...);
bool my_char_in_str(char c, char *str);

#endif /*MY_H*/
