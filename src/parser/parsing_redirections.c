/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:28:55 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/12 20:28:56 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
