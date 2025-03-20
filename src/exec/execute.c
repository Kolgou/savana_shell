#include "../../minishell.h"

static int	execute_in_child(char *path, char **args, char **env)
{
    pid_t    pid;
    int      status;

    pid = fork();
    if (pid == 0)
    {
        if (execve(path, args, env) == -1)
            exit(EXIT_FAILURE);
    }
    else 
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        else
            return (1);
    }
    return (0);
}

static int     execute_absolute_path(char **args, char **paths)
{
    char    *path;
    char    *tmp;
    int     i;

    i = 0;
    while (paths[i])
    {
        path = strdup(paths[i]);
        tmp = ft_strjoin(path, "/");
        free(path);
        path = ft_strjoin(tmp, args[0]);
        free(tmp);
        if (!access(path, F_OK | X_OK))
        {
            int ret = execute_in_child(path, args, NULL);
            free(path);
            return (ret);
        }
        free(path);
        i++;
    }
    return (1);
}

static int     execute_cmd_path(char *cmd, char **paths, char **env)
{
    int     i;
    char    *args[2];

    args[0] = cmd;
    args[1] = NULL;
    i = 0;
    if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (!access(args[0], F_OK | X_OK))
			return execute_in_child(args[0], args, env);
		printf("nul ton code\n");
		return (0);
	}
    if (!execute_absolute_path(args, paths))
        return (0);
    printf("Command not found\n");
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
        execute_cmd_path(cmd->args[0], paths, env);
    else
        printf("Please provide a command to execute\n");
    free(path);
    free(paths);
    return (1);
}
