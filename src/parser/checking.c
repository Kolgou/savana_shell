#include "../../minishell.h"

int	check_syntaxe(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE && (!current->next || !current->prev))
		{
			printf("syntax error near unexpected token `newline'\n");
			return (0);
		}
		else if ((current->type == REDIR_IN || current->type == REDIR_OUT
				|| current->type == APPEND || current->type == HEREDOC)
			&& (!current->next || (current->next->type != WORD
					&& current->next->type != SQUOTE
					&& current->next->type != DQUOTE)))
		{
			printf("syntax error near unexpected token `newline'\n");
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	check_quotes(t_token *tokens)
{
	t_token	*current;
	int		in_single_quote;
	int		in_double_quote;

	current = tokens;
	in_single_quote = 0;
	in_double_quote = 0;
	while (current)
	{
		if (current->type == SQUOTE)
			in_single_quote = !in_single_quote;
		else if (current->type == DQUOTE)
			in_double_quote = !in_double_quote;
		current = current->next;
	}
	if (in_single_quote || in_double_quote)
	{
		printf("syntax error: unterminated quote\n");
		return (0);
	}
	return (1);
}
