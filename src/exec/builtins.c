#include "../../minishell.h"

static bool is_n_option(const char *str)
{
    if (str[0] != '-')
        return (false);

    int i = 1;
    while (str[i] != '\0')
    {
        if (str[i] != 'n')
            return (false);
        i++;
    }

    return (str[1] != '\0');
}

void ft_echo(t_command *cmd, char **env)
{
    bool n_option = false;
    int i = 1;

    expand_var_env(cmd, env);
    while (cmd->args[i] && is_n_option(cmd->args[i]))
    {
        n_option = true;
        i++;
    }
    while (cmd->args[i])
    {
        printf("%s", cmd->args[i]);
        i++;
        if (cmd->args[i])
            printf(" ");
    }
    if (!n_option)
        printf("\n");
}