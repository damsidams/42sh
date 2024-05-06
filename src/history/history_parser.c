/*
** EPITECH PROJECT, 2024
** 42SH
** File description:
** File to start good history functions
*/

static bool history_sign(char const *str)
{
    if (str == NULL) {
        return false;
    }
    for (unsigned int i = 0; str[i]; i++) {
        if (str[i] == HISTORY_CHAR) {
            return true;
        }
    }
    return false;
}

char *check_if_historic(char *cmd)
{
    if (!history_sign(cmd)) {
        return cmd;
    }
}
