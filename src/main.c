#include "../minishell.h"
#include <signal.h>

static void sigint_handler(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void sigquit_handler(int sig)
{
    (void)sig;
}

void setup_signal_handling(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = SA_RESTART;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = sigquit_handler;
    sa_quit.sa_flags = SA_RESTART;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **envp)
{
    setup_signal_handling();
	using_history();
	char **env = fill_env(envp);
	while (1)
	{
		if (!build_prompt(&env))
			break ;
	}
	rl_clear_history();
	return (0);
}
