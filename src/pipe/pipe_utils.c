/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <aaitbrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:48:49 by aaitbrah          #+#    #+#             */
/*   Updated: 2025/04/17 18:58:00 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_redirect_error(t_command *cmd_list, char **env)
{
	free_commands(cmd_list);
	free_array(env);
	exit(EXIT_FAILURE);
}

void	setup_pipe_child(int *pipe_fd, int saved_stdin)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(saved_stdin);
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
}
