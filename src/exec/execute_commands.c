/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:31:07 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/12 20:31:08 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_absolute_path(char **args, char **paths, t_command *cmd, char **env)
{
	char	*path;
	char	*tmp;
	int		i;
	int		ret;

	i = 0;
	while (paths[i])
	{
		path = strdup(paths[i]);
		tmp = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(tmp, args[0]);
		free(tmp);
		if (!access(path, F_OK | X_OK))
		{
			ret = execute_in_child(path, args, env, cmd);
			free(path);
			return (ret);
		}
		free(path);
		i++;
	}
	return (-1);
}

int	execute_cmd(t_command *cmd, char **env)
{
	int		i;
	char	*path;
	char	**paths;
	int		result;

	path = NULL;
	paths = NULL;
	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH=", 5))
		{
			path = strdup(env[i] + 5);
			paths = ft_split(path, ':');
			break ;
		}
		i++;
	}
	result = -1;
	result = execute_cmd_env(cmd, paths, env);
	free(path);
	free_array(paths);
	return (result);
}

int	execute_with_redir(t_command *cmd, char ***env_ptr)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	ret = -1;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (check_if_builtin(cmd) == 1)
		ret = execute_command_by_type(cmd, env_ptr);
	else if (cmd->redirect && !apply_redirections(cmd->redirect))
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}
