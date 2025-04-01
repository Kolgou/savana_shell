#include "../minishell.h"

int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **envp)
{
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
