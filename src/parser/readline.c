#include "../../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void execute_commands(t_command *cmd_list, char **env)
{
    t_command *current = cmd_list;
    
    while (current)
    {
        printf("Command:\n");
        if (current->args && current->args[0])
        {
            printf("  Name: %s\n", current->args[0]);
            int i = 1;
            if (current->args[i])
            {
                printf("  Args: ");
                while (current->args[i])
                {
                    printf("%s ", current->args[i]);
                    i++;
                }
                printf("\n");
            }
        }
        
        if (current->redirect)
        {
            t_redirection *redir = current->redirect;
            printf("  Redirections:\n");
            while (redir)
            {
                const char *type_str;
                if (redir->type == REDIR_IN)
                    type_str = "<";
                else if (redir->type == REDIR_OUT)
                    type_str = ">";
                else if (redir->type == APPEND)
                    type_str = ">>";
                else
                    type_str = "<<";
                
                printf("    %s %s\n", type_str, redir->file);
                redir = redir->next;
            }
        }
        
        current = current->next;
        if (current)
            printf("  | (pipe)\n");
    }
    (void)env;
}

static void exec_input(char *input, char **env)
{
	t_token		*tokens;
	t_command	*cmd_list;

	tokens = tokenize_input(input);
    if (!check_syntaxe(tokens) || !check_quotes(tokens) || !*input)
		free_tokens(tokens);
	cmd_list = parse_command(tokens);
	free_tokens(tokens);
	if (cmd_list)
	{
        execute_with_redir(cmd_list, env);
		free_commands(cmd_list);
	}
}

int build_prompt(char **env)
{
    char *input;

    static char prompt[100] = "\001\033[1;32m\002المحتالون الأفارقة$ \001\033[0m\002";
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
        free(input);
        return (0);
    }
    exec_input(input, env);
    free(input);
    return (1);
}
