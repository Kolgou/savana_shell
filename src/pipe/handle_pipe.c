/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbrah <aaitbrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:32:23 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/16 19:49:41 by aaitbrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void handle_redirect_error(t_command *cmd_list, char **env)
{
    free_commands(cmd_list);
    free_array(env);
    exit(EXIT_FAILURE);
}

static void setup_pipe_child(int *pipe_fd, int saved_stdin)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    close(saved_stdin);
    close(pipe_fd[0]);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
}

static void child_processed_pcmd(t_command *current, int *pipe_fd, 
	t_pipe_data *data)
{
	setup_pipe_child(pipe_fd, data->saved_stdin);

	if (current->redirect && !apply_redirections(current->redirect))
		handle_redirect_error(data->cmd_list, data->env);

	execute_cmd(current, data->env);
	free_commands(data->cmd_list);
	free_array(data->env);
	exit(EXIT_SUCCESS);
}

static int process_piped_command(t_command *current, pid_t *pid,
	t_pipe_data *data)
{
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	*pid = fork();
	if (*pid == -1)
		return (perror("fork"), -1);

	if (*pid == 0)
		child_processed_pcmd(current, pipe_fd, data);
	else
		{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		}
	return (1);
}

static int process_last_command(t_command *current, pid_t *pid, 
	t_pipe_data *data)
{
	*pid = fork();
	if (*pid == -1)
		return (perror("fork"), -1);
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(data->saved_stdin);
		if (current->redirect && !apply_redirections(current->redirect))
			handle_redirect_error(data->cmd_list, data->env);
		execute_cmd(current, data->env);
		free_commands(data->cmd_list);
		free_array(data->env);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

int execute_pipeline(t_command *command, char **env, int saved_stdin)
{
    int status;
    pid_t pid;
    t_command *current;
    t_pipe_data data;

    data.cmd_list = command;
    data.env = env;
    data.saved_stdin = saved_stdin;
    current = command;
    while (current && current->next)
    {
        if (process_piped_command(current, &pid, &data) == -1)
            return (-1);
        current = current->next;
    }
    if (current)
    {
        if (process_last_command(current, &pid, &data) == -1)
            return (-1);
    }
    while (wait(&status) > 0)
        continue;
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
	exit_status = 0;
	exit_status = execute_pipeline(command, env, saved_stdin);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	*env_ptr = env;
	return (exit_status);
}
