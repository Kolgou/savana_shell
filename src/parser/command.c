#include "../../minishell.h"

static t_command  *create_command(void)
{
    t_command *new_commands;

    new_commands = malloc(sizeof(t_command));
    if (!new_commands)
        return (NULL);
    new_commands->args = NULL;
    new_commands->redirect = NULL;
    new_commands->next = NULL;
    new_commands->env = NULL;
    return (new_commands);
}

static void init_no_args(t_command *cmd, char *args)
{
    cmd->args = malloc(sizeof(char *) * 2);
    if (!cmd->args)
        return ;
    cmd->args[0] = ft_strdup(args);
    cmd->args[1] = NULL;
}

static int add_arguments(t_command *cmd, char *args)
{
    int     i;
    char    **new_args;

    i = 0;
    if (!cmd->args)
    {
        init_no_args(cmd, args);
        return (1);  
    }
    while (cmd->args[i])
        i++;
    new_args = malloc(sizeof(char *) * (i + 2));
    if (!new_args)
        return (0);
    i = 0;
    while (cmd->args[i])
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[i] = ft_strdup(args);
    new_args[i + 1] = NULL;
    free(cmd->args);
    cmd->args = new_args;
    return (1);
}

static int add_redirections(t_command *cmd, char *file, t_token_type type)
{
    t_redirection *redir;
    t_redirection *current;

    redir = malloc(sizeof(t_redirection));
    if (!redir)
        return (0);
    redir->type = type;
    redir->file = ft_strdup(file);
    redir->next = NULL;
    if (!cmd->redirect)
    {
        cmd->redirect = redir;
        return (1);
    }
    current = cmd->redirect;
    while (current->next)
        current = current->next;
    current->next = redir;
    return (1);
}

static int  process_tokens(t_token **c_token, t_command **c_cmd)
{
    if ((*c_token)->type == WORD)
    {
        add_arguments(*c_cmd, (*c_token)->content);
    }
    else if ((*c_token)->type == PIPE)
    {
        (*c_cmd)->next = create_command();
        if (!(*c_cmd)->next)
            return (0);
        *c_cmd = (*c_cmd)->next;
    }
    else if ((*c_token)->type == REDIR_IN || (*c_token)->type == REDIR_OUT 
            || (*c_token)->type == APPEND || (*c_token)->type == HEREDOC)
    {
        t_token_type redir_type = (*c_token)->type;
        if (!(*c_token)->next || ((*c_token)->next->type != WORD && (*c_token)->next->type != DQUOTE
            && (*c_token)->next->type != SQUOTE))
            return (0);
        if ((*c_token)->next->type == DQUOTE || (*c_token)->next->type == SQUOTE)
            (*c_token) = (*c_token)->next;
        add_redirections(*c_cmd, (*c_token)->next->content, redir_type);
        (*c_token) = (*c_token)->next;
    }
    return (1);
}

t_command   *parse_command(t_token *tokens)
{
    t_command *l_cmd;
    t_command *c_cmd;
    t_token   *c_token;

    l_cmd = create_command();
    if (!l_cmd)
        return (NULL);
    c_cmd = l_cmd;
    c_token = tokens;
    while (c_token)
    {
        if (!process_tokens(&c_token, &c_cmd))
            return (NULL);
        c_token = c_token->next;
    }
    return (l_cmd);
}
