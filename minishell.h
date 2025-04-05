#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
#include <stdbool.h>

#ifndef HOST_NAME_MAX
# define HOST_NAME_MAX 64
#endif

// Styles
#define BOLD    "\033[1m"
#define ITALIC  "\033[3m"
#define UNDER   "\033[4m"
#define RESET   "\033[0m"

// Couleurs
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

// Combinaisons
#define BOLD_RED    "\033[1;31m"
#define BOLD_GREEN  "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE   "\033[1;34m"

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
    char **args;
    t_redirection *redirect;
    struct s_command *next;
    char    **env;
    int     test;
} t_command;

//readline
int     build_prompt(char ***env_ptr);
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
char		**fill_env(char **env);

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
int     execute_cmd(t_command *cmd, char **env);
int     execute_with_redir(t_command *cmd, char ***env_ptr);

//free
void    free_tokens(t_token *tokens);
void    free_redirects(t_redirection *redirects);
void    free_commands(t_command *cmd_list);
void    free_env(char **env);

//redirections
int     apply_redirections(t_redirection *redirects);

//heredoczz
int     heredoc_redir(t_redirection *redirect);

//pipe
int     pipe_handler(t_command *command, char ***env_ptr);

//expand
int      expand_var_env(t_command *command, char **env);

//export_utils
void     sort_env(char **env);
int      check_correct_args(char *str);
char     **create_updated_env(char **env, char *new_var);

//builtins
void     ft_echo(t_command *command, char **env);
void     ft_export(t_command *cmd, char ***env_ptr);
void     ft_cd(t_command *cmd);
void     ft_env(char **env);
void     ft_unset(t_command *cmd, char ***env);
void     ft_exit(t_command *cmd);

#endif