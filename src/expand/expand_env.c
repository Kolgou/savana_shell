/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:31:51 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/12 20:31:52 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	expand_exit_status(t_command *command)
{
	int	i;

	i = 0;
	while (command->args[i])
	{
		if (command->args[i][0] == '$' && command->args[i][1] == '?')
		{
			free(command->args[i]);
			command->args[i] = ft_itoa(g_last_exit_status);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	replace_env_var(t_command *command, char **tmp)
{
	int	j;

	if (!command || !command->args)
		return (0);
	j = 0;
	while (command->args[j])
	{
		if (command->args[j] && command->args[j][0] == '$'
			&& !ft_strncmp(command->args[j] + 1, tmp[0], ft_strlen(tmp[0])))
		{
			free(command->args[j]);
			command->args[j] = ft_strdup(tmp[1]);
			return (1);
		}
		j++;
	}
	return (0);
}

int	expand_var_env(t_command *command, char **env)
{
	int		i;
	char	**tmp;
	int		found;

	if (!command || !command->args)
		return (0);
	if (expand_exit_status(command))
		return (0);
	i = 0;
	found = 0;
	while (env[i] && !found)
	{
		tmp = ft_split(env[i], '=');
		if (!tmp)
			return (0);
		found = replace_env_var(command, tmp);
		ft_free_array(tmp);
		i++;
	}
	return (found);
}
