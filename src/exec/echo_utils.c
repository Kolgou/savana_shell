#include "../../minishell.h"

bool	is_n_option(const char *str)
{
	int		i;

	if (str[0] != '-')
		return (false);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (str[1] != '\0');
}
