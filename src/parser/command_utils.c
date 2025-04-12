/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:29:17 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/12 20:29:19 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_no_args(t_command *cmd, char *args)
{
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
		return ;
	cmd->args[0] = ft_strdup(args);
	if (!cmd->args[0])
	{
		free_array(cmd->args);
		cmd->args = NULL;
		return ;
	}
	cmd->args[1] = NULL;
}

int	process_redirection(t_token **c_token, t_command **c_cmd)
{
	t_token_type	redir_type;

	redir_type = (*c_token)->type;
	if (!(*c_token)->next || ((*c_token)->next->type != WORD
			&& (*c_token)->next->type != DQUOTE
			&& (*c_token)->next->type != SQUOTE))
		return (0);
	if ((*c_token)->next->type == DQUOTE || (*c_token)->next->type == SQUOTE)
		(*c_token) = (*c_token)->next;
	add_redirections(*c_cmd, (*c_token)->next->content, redir_type);
	(*c_token) = (*c_token)->next;
	return (1);
}
