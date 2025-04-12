/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:32:06 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/12 20:32:07 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "../minishell.h"
#include <signal.h>

int			g_last_exit_status = 0;

static void	sigint_readline_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_exit_status = 130;
}

static void	sigint_execution_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	g_last_exit_status = 130;
}

void	set_signals_for_readline(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_readline_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	set_signals_for_execution(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_execution_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av,
		char **envp)
{
	char	**env;

	set_signals_for_readline();
	using_history();
	env = fill_env(envp);
	while (1)
	{
		if (!build_prompt(&env))
			break ;
	}
	free_array(env);
	rl_clear_history();
	return (0);
}
