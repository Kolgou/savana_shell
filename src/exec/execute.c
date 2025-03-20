#include "../../minishell.h"

static int     execute_ls(char *cmd, char **paths, char **env)
{
    int     i;
    char    *path;
    char    *tmp;
    char    *args[2];

    args[0] = cmd;
    args[1] = NULL;
    i = 0;
    while (paths[i])
    {
        path = strdup(paths[i]);
        tmp = ft_strjoin(path, "/");
        free(path);
        path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!access(path, F_OK | X_OK))
        {
            execve(path, args, env);
            free(path);
            return (0);
        }
        free(path);
        i++;
    }
    return (1);
}

int    execute_cmd(t_command *cmd, char **env)
{
    int     i;
    char    *path;
    char    **paths;

    path = NULL;
    paths = NULL;
    i = 0;
    while (env[i])
    {
        if (!strncmp(env[i], "PATH=", 5))
        {
            path = strdup(env[i] + 5);
            paths = ft_split(path, ':');
            break ;
        }
        i++;
    }
    if (cmd->args[0])
        execute_ls(cmd->args[0], paths, env);
    else
        printf("Please provide a command to execute\n");
    free(path);
    free(paths);
    return (1);
}