#include "../../minishell.h"

void init_data(t_data *data)
{
    data->fd[0] = -1;
    data->fd[1] = -1;
    data->pid = 0;
    data->path = NULL;
    data->paths = NULL;
    data->args = NULL;
    data->fd_stdin = -1;
    data->fd_stdout = -1;
    data->status = -1;
}