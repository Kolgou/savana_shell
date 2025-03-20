#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"

#ifndef HOST_NAME_MAX
# define HOST_NAME_MAX 64
#endif

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

typedef enum e_token_type {
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC,
    SQUOTE,
    DQUOTE,
} t_token_type;

typedef struct s_token {
    char *content;
    t_token_type type;
    struct s_token *next;
    struct s_token *prev;
} t_token;

typedef struct s_redirection {
    t_token_type type;
    char *file;
    struct s_redirection *next;
} t_redirection;

typedef struct s_command {
    char *command;
    char **args;
    t_redirection *redirect;
    struct s_command *next;
} t_command;

//readline
int     build_prompt(char **env);
int	    ft_strcmp(const char *s1, const char *s2);

//checking
int     check_syntaxe(t_token *tokens);
int     check_quotes(t_token *tokens);

//parsing
t_token *create_token(char *content, t_token_type type);
void    add_token(t_token **tokens, t_token *new_token);
t_token *tokenize_input(char *input);
int     check_syntaxe(t_token *tokens);
void    print_tokens(t_token *tokens);

//parsing utils
int     is_operator_char(char c);
int     is_whitespace(char c);
int     get_word_length(char *input, int i);

//parsing word
void    handle_word(t_token **tokens, char *input, int *i);
void    handle_quoted_word(t_token **tokens, char *input, int *i);

//parsing redirection
void    handle_input_redirection(t_token **tokens, char *input, int *i);
void    handle_output_redirection(t_token **tokens, char *input, int *i);
void	handle_quote(t_token **tokens, char *input, int *i);

//command 
t_command   *parse_command(t_token *tokens);

//execute
int    execute_cmd(t_command *cmd, char **env);

//free
void    free_tokens(t_token *tokens);
void    free_redirects(t_redirection *redirects);
void    free_commands(t_command *cmd_list);

#endif