#include "../../minishell.h"

void	handle_word(t_token **tokens, char *input, int *i)
{
	int		word_len;
	char	*word;

	word_len = get_word_length(input, *i);
	word = malloc(word_len + 1);
	if (!word)
		return ;
	ft_strlcpy(word, &input[*i], word_len + 1);
	add_token(tokens, create_token(word, WORD));
	free(word);
	(*i) += word_len;
}

static char	*extract_quoted_word(char *input, int *i)
{
	char	quote_type;
	int		start;
	int		len;
	char	*word;

	quote_type = input[*i];
	start = *i + 1;
	len = 0;
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
	{
		(*i)++;
		len++;
	}
	if (input[*i] == quote_type)
		(*i)++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, &input[start], len + 1);
	return (word);
}

void	handle_quoted_word(t_token **tokens, char *input, int *i)
{
	char *word;

	word = extract_quoted_word(input, i);
	if (!word)
		return ;
	add_token(tokens, create_token(word, WORD));
	free(word);
}