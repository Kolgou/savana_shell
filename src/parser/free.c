#include "../../minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

void	free_redirects(t_redirection *redirects)
{
	t_redirection	*next;

	while (redirects)
	{
		next = redirects->next;
		free(redirects->file);
		free(redirects);
		redirects = next;
	}
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_commands(t_command *cmd_list)
{
	t_command	*next;

	while (cmd_list)
	{
		next = cmd_list->next;
		free_array(cmd_list->args);
		free_redirects(cmd_list->redirect);
		free(cmd_list);
		cmd_list = next;
	}
}
