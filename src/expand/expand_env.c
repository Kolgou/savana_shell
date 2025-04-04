#include "../../minishell.h"

static void ft_free_array(char **array)
{
    int i;
    
    if (!array)
        return;
        
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

int     expand_var_env(t_command *command, char **env)
{
    int     i;
    int     j;
    char    **tmp;

    i = 0;
    tmp = NULL;
    while (env[i])
    {
        tmp = ft_split(env[i], '=');
        if (!tmp)
            return (0);
        j = 0;
        while (command->args[j])
        {
            if (command->args[j] && !ft_strncmp(command->args[j] + 1, tmp[0], ft_strlen(tmp[0])))
            {
                free(command->args[j]);
                command->args[j] = ft_strdup(tmp[1]);
                ft_free_array(tmp);
                return (1);
            }
            j++;
        }
        ft_free_array(tmp);
        i++;
    }
    return (0);
}

