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

void    handle_quote(t_token **tokens, char *input, int *i)
{
    char quote_type;
    int len;
    char *word;
    
    quote_type = input[*i];
    if (quote_type == '\'' || quote_type == '\"')
    {
        len = 1;
        if (quote_type == '\"')
        {
            (*i)++;
            len = 0;
        }
        while (input[*i + len] && input[*i + len] != quote_type)
            len++;
        if (input[*i + len] == '\'')
            len++;
        if (len > 0)
        {
            word = malloc(len + 1);
            if (word)
            {
                ft_strlcpy(word, &input[*i], len + 1);
                add_token(tokens, create_token(word, WORD));
                free(word);
            }
        }
        *i += len;
        if (quote_type == '\"' && input[*i] == quote_type)
            (*i)++;
    }
}
