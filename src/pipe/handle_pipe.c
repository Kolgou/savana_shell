/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:32:23 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/12 20:33:55 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	child_processed_pcmd(t_command *current, int *pipe_fd,
	char **env, int saved_stdin)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(saved_stdin);
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	if (current->redirect && !apply_redirections(current->redirect))
	{
		free_commands(current);
		free_array(env);
		exit(EXIT_FAILURE);
	}
	execute_cmd(current, env);
	free_commands(current);
	free_array(env);
	exit(EXIT_SUCCESS);
}

static int	process_piped_command(t_command *current, pid_t *pid,
		char **env, int saved_stdin)
{
	int			pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	*pid = fork();
	if (*pid == -1)
		return (perror("fork"), -1);
	
	if (*pid == 0)
	{
		child_processed_pcmd(current, pipe_fd, env, saved_stdin);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	return (1);
}

static int	process_last_command(t_command *current, pid_t *pid, char **env,
		int saved_stdin)
{
	*pid = fork();
	if (*pid == -1)
		return (perror("fork"), -1);
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(saved_stdin);
		if (current->redirect && !apply_redirections(current->redirect))
		{
			free_commands(current);
			free_array(env);
			exit(EXIT_FAILURE);
		}
		execute_cmd(current, env);
		free_commands(current);
		free_array(env);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

static int	execute_pipeline(t_command *command, char **env, int saved_stdin)
{
	int			status;
	pid_t		pid;
	t_command	*current;

	current = command;
	while (current && current->next)
	{
		if (process_piped_command(current, &pid, env, saved_stdin) == -1)
			return (-1);
		current = current->next;
	}
	if (current)
	{
		if (process_last_command(current, &pid, env, saved_stdin) == -1)
			return (-1);
	}
	while (wait(&status) > 0)
		continue ;
	return (WEXITSTATUS(status));
}

int	pipe_handler(t_command *command, char ***env_ptr)
{
	int		saved_stdin;
	int		exit_status;
	char	**env;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
	{
		return (-1);
	}
	env = *env_ptr;
	exit_status = execute_pipeline(command, env, saved_stdin);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	*env_ptr = env;
	return (exit_status);
}
