/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:30:25 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/12 20:30:26 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(t_command *cmd)
{
	bool	n_option;
	int		i;

	n_option = false;
	i = 1;
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

int	ft_export(t_command *cmd, char ***env_ptr)
{
	char	*new_var;
	char	**env;

	env = *env_ptr;
	if (!cmd->args[1])
	{
		sort_env(cmd->env);
		return (0);
	}
	if (!check_correct_args(cmd->args[1]))
	{
		printf("Export failed: invalid identifier\n");
		return (1);
	}
	new_var = ft_strdup(cmd->args[1]);
	if (!new_var)
		return (1);
	create_new_env(new_var, env, env_ptr, cmd);
	return (0);
}

int	ft_cd(t_command *cmd)
{
	if (!cmd->args[1])
	{
		printf(BOLD_RED "cd: missing argument\n");
		return (1);
	}
	if (chdir(cmd->args[1]) != 0)
	{
		perror(BOLD_RED "cd");
		return (1);
	}
	return (0);
}

int	ft_env(char **env)
{
	if (!env)
		return (1);
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}

int	ft_unset(t_command *cmd, char ***env)
{
	int	i;
	int	count;

	count = 0;
	while ((*env)[count])
		count++;
	if (!cmd->args[1])
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		remove_env_var(env, cmd->args[i], &count);
		i++;
	}
	return (0);
}

static bool	is_numeric(const char *str)
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

int	ft_exit(t_command *cmd)
{
	printf("exit\n");
	if (cmd->args[1] && cmd->args[2])
	{
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			printf("bash: exit: %s: numeric argument required\n", cmd->args[1]);
			exit(255);
		}
		exit(ft_atoi(cmd->args[1]) % 256);
	}
	exit(0);
	return (0);
}
