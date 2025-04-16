/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_path_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <aaitbrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:34:21 by aaitbrah          #+#    #+#             */
/*   Updated: 2025/04/16 16:48:35 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_child_process(char *path, char **args, char **env,
		t_command *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->redirect)
	{
		if (!apply_redirections(cmd->redirect))
		{
			free_commands(cmd);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	if (execve(path, args, env) == -1)
	{
		free_commands(cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
	free_commands(cmd);
	free(path);
	exit(EXIT_SUCCESS);
}
