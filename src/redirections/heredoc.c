/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:31:36 by alaualik          #+#    #+#             */
/*   Updated: 2025/04/12 20:31:37 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	loop_redir(t_redirection *redirect, char *line, int fd)
{
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redirect->file))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	heredoc_redir(t_redirection *redirect)
{
	char	*line;
	int		fd;
	char	*tmp_file;

	tmp_file = "/tmp/minishell_heredoc";
	line = NULL;
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	loop_redir(redirect, line, fd);
	close(fd);
	fd = open(tmp_file, O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(tmp_file);
	return (fd);
}
