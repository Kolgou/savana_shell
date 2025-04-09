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
	t_redirection	*current;
	t_redirection	*next;

	current = redirects;
	while (current)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
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
	t_command	*current;
	t_command	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			free_array(current->args);
		}
		if (current->redirect)
			free_redirects(current->redirect);
		free(current);
		current = next;
	}
}
