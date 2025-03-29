#include "../../minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	get_word_length(char *input, int i)
{
	int	len;
	int	in_single_quote;
	int	in_double_quote;

	len = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (input[i + len])
	{
		if (input[i + len] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i + len] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote)
		{
			if (is_whitespace(input[i + len]) || is_operator_char(input[i
					+ len]))
				break ;
		}
		len++;
	}
	return (len);
}

