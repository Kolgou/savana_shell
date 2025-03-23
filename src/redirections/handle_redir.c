#include "../../minishell.h"

static int input_redir(t_redirection *redirect)
{
    int fd;
    
    fd = open(redirect->file, O_RDONLY);
    if (fd == -1)
        return (0);
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (1);
}

static int output_redir(t_redirection *redirect)
{
    int fd;
    
    fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (0);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (1);
}

static int append_redir(t_redirection *redirect)
{
    int fd;

    fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        return (0);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (1);
}

int apply_redirections(t_redirection *redirects)
{
    t_redirection *current;
    
    current = redirects;
    while (current)
    {
        if (current->type == REDIR_IN)
        {
            if (!input_redir(current))
                return (0);
        }
        else if (current->type == REDIR_OUT)
        {
            if (!output_redir(current))
                return (0);
        }
        else if (current->type == APPEND)
        {
            if (!append_redir(current))
                return (0);
        }
        current = current->next;
    }
    return (1);
}
