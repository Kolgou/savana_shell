/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <aaitbrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:30:18 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/16 16:34:14 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_in_child(char *path, char **args, char **env, t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		execute_child_process(path, args, env, cmd);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
	return (0);
}

int	handle_direct_path(t_command *cmd, char **env)
{
	struct stat	path_stat;

	if (cmd->args[0] && stat(cmd->args[0], &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			printf("%s: Is a directory\n", cmd->args[0]);
			return (126);
		}
	}
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (!access(cmd->args[0], F_OK | X_OK))
			return (execute_in_child(cmd->args[0], cmd->args, env, cmd));
		printf(BOLD_RED "أمر: %s: No such file or directory\n", cmd->args[0]);
		return (127);
	}
	return (-2);
}

int	execute_cmd_env(t_command *cmd, char **paths, char **env)
{
	int	ret;

	ret = handle_direct_path(cmd, env);
	if (ret != -2)
		return (ret);
	ret = execute_absolute_path(cmd->args, paths, cmd, env);
	if (ret == -1)
	{
		printf(BOLD_RED "Command %s not found 🤓\n", cmd->args[0]);
		return (127);
	}
	return (ret);
}

int	check_if_builtin(t_command *cmd)
{
	if (cmd->args && !ft_strcmp(cmd->args[0], "echo"))
		return (1);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "exit"))
		return (1);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "export"))
		return (1);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "cd"))
		return (1);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "env"))
		return (1);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "unset"))
		return (1);
	else if (cmd->args && cmd->args[0])
		return (1);
	return (0);
}

int	execute_command_by_type(t_command *cmd, char ***env_ptr)
{
	char	**env;

	env = *env_ptr;
	if (cmd->single_quotes == false)
		cmd->exit_s = expand_var_env(cmd, *env_ptr);
	if (cmd->args && !ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "export"))
		cmd->exit_s = ft_export(cmd, env_ptr);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "exit"))
		cmd->exit_s = ft_exit(cmd);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "cd"))
		cmd->exit_s = ft_cd(cmd);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "env"))
		cmd->exit_s = ft_env(env);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "unset"))
		cmd->exit_s = ft_unset(cmd, env_ptr);
	else if (cmd->args && cmd->args[0])
		cmd->exit_s = execute_cmd(cmd, env);
	return (cmd->exit_s);
}
