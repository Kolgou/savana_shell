NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

LIBFT_DIR = libft



SRC_DIR = src
SRC_FILES = parser/readline.c \
         parser/parsing.c \
         parser/parsing_utils.c \
         parser/parsing_redirections.c \
         parser/parsing_words.c \
         parser/free.c \
		 parser/command.c \
		 parser/checking.c \
		 exec/execute_cmd_path.c \
		 exec/builtins.c \
		 exec/export_utils.c \
		 redirections/handle_redir.c \
		 redirections/heredoc.c \
		 pipe/handle_pipe.c \
		 expand/expand_env.c \
         main.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
    
OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "Compilation de minishell terminée"
	@make -s africa

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
    
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) clean
	@echo "Clean terminée"

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean
	@echo "Fclean terminée"

re: fclean all

africa:
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[1;37m⬜⬜⬜\033[0;30m⬛⬛\033[1;37m⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥🟥🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[1;37m⬜⬜⬜⬜\033[0;31m🟥🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩\033[1;37m⬜⬜⬜⬜⬜⬜\033[0;31m🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥\033[0;32m🟩🟩🟩\033[1;37m⬜⬜\033[0;31m🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩🟩🟩\033[1;37m⬜⬜\033[0;31m🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛\033[0;32m🟩\033[0;30m⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩🟩🟩\033[0;31m🟥🟥🟥🟥🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩🟩🟩\033[1;37m⬜\033[0;31m🟥🟥🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩🟩🟩\033[1;37m⬜\033[0;31m🟥🟥🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩🟩🟩\033[1;37m⬜\033[0;31m🟥\033[1;37m⬜\033[0;31m🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩🟩🟩\033[0;31m🟥\033[1;37m⬜⬜⬜\033[0;31m🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥\033[0;32m🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[0;32m🟩\033[1;37m⬜⬜⬜⬜⬜⬜\033[0;31m🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥\033[1;37m⬜⬜⬜⬜\033[0;31m🟥🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[0;31m🟥🟥🟥🟥🟥\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[0;32m🟩🟩\033[1;37m⬜⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[1;37m⬜⬜⬜⬜⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\033[1;37m⬜⬜⬜\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0;30m⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛"
	@echo "\033[0m"
	@echo "\033[1;32m                                                                          				\033[0m"
	@echo "\033[1;32m                                                                          				\033[0m"
	@echo "\033[1;32m      ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗       \033[0m"
	@echo "\033[1;32m      ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║       \033[0m"
	@echo "\033[1;32m      ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║       \033[0m"
	@echo "\033[1;32m      ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║       \033[0m"
	@echo "\033[1;32m      ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗  \033[0m"
	@echo "\033[1;32m      ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝  \033[0m"
	@echo "\033[1;32m                               AFRIQUE 🌍                                             \033[0m"
	@echo "\033[1;32m                                                                          				\033[0m"
	@echo "\033[1;32m                                                                          				\033[0m"
	@echo "\033[1;32m                                                                          				\033[0m"

.PHONY: all clean fclean re