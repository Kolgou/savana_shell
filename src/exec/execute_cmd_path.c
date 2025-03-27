#include "../../minishell.h"
#include <stdbool.h>

static int	execute_in_child(char *path, char **args, char **env, t_redirection *redirects)
{
    pid_t    pid;
    int      status;

    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL); 
        signal(SIGQUIT, SIG_DFL);
        if (redirects)
            if (!apply_redirections(redirects))
                exit(EXIT_FAILURE);
        if (execve(path, args, env) == -1)
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
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

static int execute_absolute_path(char **args, char **paths, t_command *cmd, char **env)
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
            int ret = execute_in_child(path, args, env, cmd->redirect);
            free(path);
            return (ret);
        }
        free(path);
        i++;
    }
    return (-1);
}

static int execute_cmd_env(t_command *cmd, char **paths, char **env)
{
    if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (!access(cmd->args[0], F_OK | X_OK))
			return execute_in_child(cmd->args[0], cmd->args, env, cmd->redirect);
        printf(BOLD_RED "أمر: %s: No such file or directory\n", cmd->args[0]);
		return (127);
	}
    int ret = execute_absolute_path(cmd->args, paths, cmd, env);
    if (ret == -1)
    {
        printf(BOLD_RED "Command %s not found 🤓\n", cmd->args[0]);
        return (127);
    }
    return (ret);
}

static bool is_n_option(const char *str)
{
    if (str[0] != '-')
        return (false);

    int i = 1;
    while (str[i] != '\0')
    {
        if (str[i] != 'n')
            return (false);
        i++;
    }

    return (str[1] != '\0');
}

static void handle_echo(t_command *cmd)
{
    bool n_option = false;
    int i = 1;

    while (cmd->args[i] && is_n_option(cmd->args[i]))
    {
        n_option = true;
        i++;
    }

    while (cmd->args[i])
    {
        printf("%s", cmd->args[i]);
        i++;
        if (cmd->args[i])
            printf(" ");
    }

    if (!n_option)
        printf("\n");
}

static void handle_cd(t_command *cmd)
{
    if (!cmd->args[1])
    {
        printf(BOLD_RED "cd: missing argument\n");
        return;
    }
    if (chdir(cmd->args[1]) != 0)
    {
        perror(BOLD_RED "cd");
    }
}

static int execute_cmd(t_command *cmd, char **env)
{
    int     i;
    char    *path;
    char    **paths;
    int     result;

    if (cmd->args && cmd->args[0] && strcmp(cmd->args[0], "env") == 0)
    {
        i = 0;
        while (env[i])
        {
            printf("%s\n", env[i]);
            i++;
        }
        return (0);
    }

    if (cmd->args && cmd->args[0] && strcmp(cmd->args[0], "echo") == 0)
    {
        handle_echo(cmd);
        return (0);
    }

    if (cmd->args && cmd->args[0] && strcmp(cmd->args[0], "cd") == 0)
    {
        handle_cd(cmd);
        return (0);
    }

    path = NULL;
    paths = NULL;
    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PATH=", 5))
        {
            path = ft_strdup(env[i] + 5);
            paths = ft_split(path, ':');
            break;
        }
        i++;
    }
    result = -1;
    result = execute_cmd_env(cmd, paths, env);
    free(path);
    free(paths);
    return (result);
}

void execute_with_redir(t_command *cmd, char **env)
{
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    if (cmd->args && cmd->args[0])
        execute_cmd(cmd, env);
    else if (cmd->redirect && !apply_redirections(cmd->redirect))
    {
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
        return;
    }
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}
