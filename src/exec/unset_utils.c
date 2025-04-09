#include "../../minishell.h"

static void	shift_env_variables(char ***env, int position, int *count)
{
	int	k;

	free((*env)[position]);
	k = position;
	while (k < *count - 1)
	{
		(*env)[k] = (*env)[k + 1];
		k++;
	}
	(*env)[*count - 1] = NULL;
	(*count)--;
}

int	remove_env_var(char ***env, const char *var_name, int *count)
{
	int	j;
	int	varlen;
	int	removed;

	j = 0;
	varlen = ft_strlen(var_name);
	removed = 0;
	while (j < *count)
	{
		if (ft_strncmp((*env)[j], var_name, varlen) == 0
			&& (*env)[j][varlen] == '=')
		{
			shift_env_variables(env, j, count);
			removed = 1;
			j--;
		}
		j++;
	}
	return (removed);
}
