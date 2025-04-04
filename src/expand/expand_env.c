
#include "../../minishell.h"

static void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	contains_single_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'')
			return (1);
		str++;
	}
	return (0);
}

static char	*ft_str_replace(char *str, char *pattern, char *replacement)
{
	char	*result;
	char	*tmp[3];
	int		len[2];
	int		count;
	int		len_front;

	count = 0;
	len[0] = ft_strlen(pattern);
	len[1] = ft_strlen(replacement);
	tmp[0] = str;
	while ((tmp[0] = ft_strstr(tmp[0], pattern)))
	{
		count++;
		tmp[0] += len[0];
	}
	result = malloc(ft_strlen(str) + (len[1] - len[0]) * count + 1);
	if (!result)
		return (NULL);
	tmp[1] = result;
	tmp[2] = str;
	while (count--)
	{
		tmp[0] = ft_strstr(tmp[2], pattern);
		len_front = tmp[0] - tmp[2];
		tmp[1] = ft_strncpy(tmp[1], tmp[2], len_front) + len_front;
		tmp[1] = ft_strcpy(tmp[1], replacement) + len[1];
		tmp[2] = tmp[0] + len[0];
	}
	ft_strcpy(tmp[1], tmp[2]);
	return (result);
}

static char	*get_var_value(char *var_name, char **env)
{
	int		i;
	char	**tmp;
	size_t	name_len;

	if (!var_name || !*var_name)
		return (NULL);
	name_len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, name_len) == 0
			&& env[i][name_len] == '=')
		{
			tmp = ft_split(env[i], '=');
			if (!tmp || !tmp[1])
			{
				ft_free_array(tmp);
				return (NULL);
			}
			var_name = ft_strdup(tmp[1]);
			ft_free_array(tmp);
			return (var_name);
		}
		i++;
	}
	return (NULL);
}

int expand_var_env(t_command *cmd, char **env)
{
    int     i;
    int     modified;
    char    *dollar_pos;
    char    *new_arg;
    char    *var_value;

    i = 0;
    modified = 0;
    while (cmd->args[i])
    {
        dollar_pos = ft_strchr(cmd->args[i], '$');
        if (dollar_pos && !contains_single_quote(cmd->args[i]))
        {
            var_value = get_var_value(dollar_pos + 1, env);
            if (var_value == NULL)
                var_value = "";
            
            new_arg = ft_str_replace(cmd->args[i], dollar_pos, var_value);
            if (new_arg)
            {
                free(cmd->args[i]);
                cmd->args[i] = new_arg;
                modified = 1;
            }
        }
        i++;
    }
    return (modified);
}
