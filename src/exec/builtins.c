/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <aaitbrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:30:25 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/17 19:40:00 by aaitbrah         ###   ########.fr       */
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

static int	process_export_arg(char *arg, char ***env_ptr, char **env,
		t_command *cmd)
{
	char	*new_var;

	if (arg[0] == '=')
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	if (!check_correct_args(arg))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	new_var = ft_strdup(arg);
	if (!new_var)
		return (1);
	create_new_env(new_var, env, env_ptr, cmd);
	return (0);
}

int	ft_export(t_command *cmd, char ***env_ptr)
{
	char	**env;
	int		i;
	int		status;

	env = *env_ptr;
	status = 0;
	if (!cmd->args[1])
	{
		sort_env(cmd->env);
		return (0);
	}
	i = 1;
	while (cmd->args[i])
	{
		status |= process_export_arg(cmd->args[i], env_ptr, env, cmd);
		i++;
	}
	return (status);
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
