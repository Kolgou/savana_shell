#include "../../minishell.h"

t_token	*create_token(char *content, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	token->single_quotes_t = false;
	if (!token->content)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new_token;
		new_token->prev = NULL;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

static void	handle_operator(t_token **tokens, char *input, int *i)
{
	if (input[*i] == '|')
	{
		add_token(tokens, create_token("|", PIPE));
		(*i)++;
	}
	else if (input[*i] == '<')
		handle_input_redirection(tokens, input, i);
	else if (input[*i] == '>')
		handle_output_redirection(tokens, input, i);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (is_whitespace(input[i]))
			i++;
		else if (is_operator_char(input[i]))
			handle_operator(&tokens, input, &i);
		else if (input[i] == '\'' || input[i] == '\"')
			handle_quote(&tokens, input, &i);
		else
			handle_word(&tokens, input, &i);
	}
	return (tokens);
}
