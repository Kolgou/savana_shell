#include "../../minishell.h"

static void     loop_sort_env(int count, char **sort)
{
    int     i;
    int     j;
    char    *temp;

    i = -1;
    temp = NULL;
    while (++i < count - 1)
    {
        j = -1;
        while (++j < count - 1)
        {
            if (ft_strcmp(sort[j], sort[j + 1]) > 0)
            {
                temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
            }
        }
    }
}

void     sort_env(char **env)
{
    int     i;
    int     count;
    char    **sort;

    sort = NULL;
    count = 0;
    while (env[count])
        count++;
    sort = malloc(sizeof(char*) * (count + 1));
    if (!sort)
        return ;
    i = -1;
    while (++i < count)
        sort[i] = ft_strdup(env[i]);
    sort[count] = NULL;
    loop_sort_env(count, sort);
    i = -1;
    while (++i < count)
        printf("declare -x %s\n", sort[i]);
}
