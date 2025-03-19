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

void handle_quote(t_token **tokens, char *input, int *i)
{
    char quote_type;
    int start;
    int len;
    
    quote_type = input[*i];
    if (quote_type == '\"')
        add_token(tokens, create_token("\"", DQUOTE));
    else
        add_token(tokens, create_token("\'", SQUOTE));
    (*i)++;
    start = *i;
    len = 0;
    while (input[*i + len] && input[*i + len] != quote_type)
        len++;
    if (len > 0)
    {
        char *word = malloc(len + 1);
        if (word)
        {
            ft_strlcpy(word, &input[start], len + 1);
            add_token(tokens, create_token(word, WORD));
            free(word);
        }
    }
    *i += len;
    if (input[*i] == quote_type)
    {
        if (quote_type == '\"')
            add_token(tokens, create_token("\"", DQUOTE));
        else
            add_token(tokens, create_token("\'", SQUOTE));
        (*i)++;
    }
}
