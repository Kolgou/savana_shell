#include "../minishell.h"

int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **env)
{
	using_history();
	while (1)
	{
		if (!build_prompt(env))
			break ;
	}
	rl_clear_history();
	return (0);
}
