#include "../../minishell.h"

static int process_piped_command(t_command *current, int *pipe_fd, 
                                      pid_t *pid, char **env)
{
    if (pipe(pipe_fd) == -1)
        return (perror("pipe"), -1);
    *pid = fork();
    if (*pid == -1)
        return (perror("fork"), -1);
    if (*pid == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        if (current->redirect && !apply_redirections(current->redirect))
            exit(EXIT_FAILURE);
        execute_cmd(current, env);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
    }
    return (1);
}

static int process_last_command(t_command *current, pid_t *pid, char **env)
{
    *pid = fork();
    if (*pid == -1)
        return (perror("fork"), -1);
    if (*pid == 0)
    {
        if (current->redirect && !apply_redirections(current->redirect))
            exit(EXIT_FAILURE);
        execute_cmd(current, env);
        exit(EXIT_SUCCESS);
    }
    return (1);
}

int pipe_handler(t_command *command, char ***env_ptr)
{
    int pipe_fd[2];
    int status;
    pid_t pid;
    t_command *current = command;
    int saved_stdin = dup(STDIN_FILENO);
    char **env = *env_ptr;

    while (current && current->next)
    {
        if (process_piped_command(current, pipe_fd, &pid, env) == -1)
            return (-1);
        current = current->next;
    }
    if (current)
    {
        if (process_last_command(current, &pid, env) == -1)
            return (-1);
    }
    while (wait(&status) > 0)
        continue;
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
    *env_ptr = env;
    return (WEXITSTATUS(status));
}

