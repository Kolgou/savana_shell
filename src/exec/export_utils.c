/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:30:48 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/12 20:30:49 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	loop_sort_env(int count, char **sort)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	temp = NULL;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - 1)
		{
			if (ft_strcmp(sort[j], sort[j + 1]) > 0)
			{
				temp = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = temp;
			}
		}
	}
}

void	sort_env(char **env)
{
	int		i;
	int		count;
	char	**sort;

	sort = NULL;
	count = 0;
	while (env[count])
		count++;
	sort = malloc(sizeof(char *) * (count + 1));
	if (!sort)
		return ;
	i = -1;
	while (++i < count)
		sort[i] = ft_strdup(env[i]);
	sort[count] = NULL;
	loop_sort_env(count, sort);
	i = -1;
	while (++i < count)
		printf("declare -x %s\n", sort[i]);
}

int	check_correct_args(char *str)
{
	int		i;
	char	**tmp;

	i = 1;
	tmp = ft_split(str, '=');
	if (((tmp[0][0] < 'A' || tmp[0][0] > 'Z') && tmp[0][0] != '_') || !tmp[1])
		return (0);
	while (tmp[0][i])
	{
		if ((tmp[0][i] < 'A' || tmp[0][i] > 'Z') && tmp[0][i] != '_'
			&& (tmp[0][i] < '0' || tmp[0][i] > '9'))
			return (0);
		i++;
	}
	if (tmp)
		free_array(tmp);
	return (1);
}

char	**create_updated_env(char **env, char *new_var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return (NULL);
	}
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env);
}

void	create_new_env(char *new_var, char **env, char ***env_ptr,
		t_command *cmd)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return ;
	}
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	if (*env_ptr != env && *env_ptr != cmd->env)
		free_array(*env_ptr);
	cmd->env = new_env;
	*env_ptr = new_env;
}
