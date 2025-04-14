#include "../../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static t_command	*prepare_command(char *input, char ***env_ptr,
		int *has_pipes)
{
	t_token		*tokens;
	t_token		*current;
	t_command	*cmd_list;

	*has_pipes = 0;
	tokens = tokenize_input(input);
	if (!check_syntaxe(tokens) || !check_quotes(tokens) || !*input)
	{
		free_tokens(tokens);
		return (NULL);
	}
	current = tokens;
	cmd_list = parse_command(tokens);
	if (cmd_list)
	{
		cmd_list->env = *env_ptr;
		cmd_list->exit_s = g_last_exit_status;
		while (current)
		{
			if (current->type == PIPE)
				*has_pipes = 1;
			current = current->next;
		}
	}
	return (free_tokens(tokens), cmd_list);
}

static void	exec_input(char *input, char ***env_ptr)
{
	t_command	*cmd_list;
	int			has_pipes;

	cmd_list = prepare_command(input, env_ptr, &has_pipes);
	if (cmd_list)
	{
		set_signals_for_execution();
		if (has_pipes)
			g_last_exit_status = pipe_handler(cmd_list, env_ptr);
		else
			g_last_exit_status = execute_with_redir(cmd_list, env_ptr);
	}
	free_commands(cmd_list);
}

int	build_prompt(char ***env_ptr)
{
	char		*input;
	static char	prompt[100];

	strcpy(prompt, "\001\033[1;32m\002المحتالون الأفارقة$ \001\033[0m\002");
	input = readline(prompt);
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	if (*input)
		add_history(input);
	if (ft_strcmp(input, "exit") == 0)
	{
		printf("exit\n");
		free(input);
		return (0);
	}
	exec_input(input, env_ptr);
	free(input);
	return (1);
}
