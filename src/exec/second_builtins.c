/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:14:42 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/14 11:20:01 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
