#include "../../minishell.h"

void	handle_input_redirection(t_token **tokens, char *input, int *i)
{
	if (input[*i + 1] == '<')
	{
		add_token(tokens, create_token("<<", HEREDOC));
		(*i) += 2;
	}
	else
	{
		add_token(tokens, create_token("<", REDIR_IN));
		(*i)++;
	}
}

void	handle_output_redirection(t_token **tokens, char *input, int *i)
{
	if (input[*i + 1] == '>')
	{
		add_token(tokens, create_token(">>", APPEND));
		(*i) += 2;
	}
	else
	{
		add_token(tokens, create_token(">", REDIR_OUT));
		(*i)++;
	}
}

