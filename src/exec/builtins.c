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

void    ft_echo(t_command *cmd, char **env)
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

void ft_export(t_command *cmd, char ***env_ptr)
{
    int i;
    char *new_var;
    char **new_env;
    char **env = *env_ptr;

    if (!cmd->args[1])
    {
        sort_env(cmd->env);
        return;
    }
    if (!check_correct_args(cmd->args[1]))
    {
        printf("Export failed: invalid identifier\n");
        return;
    }
    new_var = ft_strdup(cmd->args[1]);
    if (!new_var)
        return;
    i = 0;
    while (env[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
    {
        free(new_var);
        return;
    }
    i = 0;
    while (env[i])
    {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = new_var;
    new_env[i + 1] = NULL;
    if (cmd->env != env)
        free(cmd->env);
    cmd->env = new_env;
    *env_ptr = new_env;
}

void    ft_cd(t_command *cmd)
{
    if (!cmd->args[1])
    {
        printf(BOLD_RED "cd: missing argument\n");
        return;
    }
    if (chdir(cmd->args[1]) != 0)
    {
        perror(BOLD_RED "cd");
    }
}

void    ft_env(char **env)
{
    if (!env)
        return ;
    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}

void ft_unset(t_command *cmd, char ***env)
{
    int i;
    int j;
    int k;
    int count = 0;
    int varlen;

    while ((*env)[count])
        count++;

    if (!cmd->args[1])
        return;

    i = 1;
    while (cmd->args[i])
    {
        varlen = ft_strlen(cmd->args[i]);
        j = 0;
        while (j < count)
        {
            if (ft_strncmp((*env)[j], cmd->args[i], varlen) == 0 && (*env)[j][varlen] == '=')
            {
                free((*env)[j]);

                k = j;
                while (k < count - 1)
                {
                    (*env)[k] = (*env)[k + 1];
                    k++;
                }
                (*env)[count - 1] = NULL;
                count--;
                j--;
            }
            j++;
        }
        i++;
    }
}

static bool is_numeric(const char *str)
{
    if (!str || *str == '\0')
        return (false);
    if (*str == '-' || *str == '+')
        str++;
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return (false);
        str++;
    }
    return (true);
}

static void print_error(const char *prefix, const char *arg, const char *suffix)
{
    if (prefix)
        write(STDERR_FILENO, prefix, ft_strlen(prefix));
    if (arg)
        write(STDERR_FILENO, arg, ft_strlen(arg));
    if (suffix)
        write(STDERR_FILENO, suffix, ft_strlen(suffix));
}

void ft_exit(t_command *cmd)
{
    write(STDOUT_FILENO, "exit\n", 5);
    if (cmd->args[1] && cmd->args[2])
    {
        print_error("bash: exit: ", NULL, "too many arguments\n");
        return ;
    }
    if (cmd->args[1])
    {
        if (!is_numeric(cmd->args[1]))
        {
            print_error("bash: exit: ", cmd->args[1], ": numeric argument required\n");
            exit(255);
        }
        exit(ft_atoi(cmd->args[1]) % 256);
    }
    exit(0);
}