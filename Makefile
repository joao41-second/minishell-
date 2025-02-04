# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 06:17:31 by jperpect          #+#    #+#              #
#    Updated: 2025/02/04 15:32:34 by rpires-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler flags
WFLGS = -Wall -Wextra -Werror
READ_FLG = -g 
FLGS = $(WFLGS) $(READ_FLG)

VAL = valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes  --suppressions=readline.supp 

# Make flags
MAKEFLAGS += -s

# Source files
SRCS = \
./src/extra/add_shlvl.c \
./src/herdoc/gen_file_redict.c \
./src/builtins/echo/ft_echo.c \
./src/parsing/syntax_checker/handle_pipe_syntax.c \
./src/parsing/syntax_checker/handle_redirection_syntax.c \
./src/parsing/syntax_checker/handle_env_variables_syntax.c \
./src/parsing/syntax_checker/handle_cd_syntax.c \
./src/parsing/syntax_checker/handle_quote_syntax.c \
./src/parsing/syntax_checker/check_syntax.c \
./src/parsing/tokenizer/chek_null_expand.c \
./src/herdoc/set_redir_pd.c \
./src/herdoc/herdoc/herdoc_expand_env.c \
./src/herdoc/herdoc/herdoc.c \
./src/herdoc/set_redir.c \
./src/comands_line/readline_utils.c \
./src/comands_line/readline_utils_extra.c \
./src/comands_line/readline.c \
./src/comands_line/signal.c \
./src/builtins/builtins.c \
./src/builtins/export/export.c \
./src/builtins/export/export_util.c \
./src/builtins/export/export_extra.c \
./src/builtins/export/organizer.c \
./src/builtins/exit/exit.c \
./src/builtins/pwd/pwd.c \
./src/Pipex/error_utils.c \
./src/Pipex/error_warnings.c \
./src/Pipex/execute_utils.c \
./src/Pipex/execute.c \
./src/Pipex/merge_tokens.c \
./src/Pipex/pipex_utils.c \
./src/Pipex/tree_functions.c \
./src/parsing/tokenizer/tokenizer.c \
./src/parsing/tokenizer/tokenizer_aux.c \
./src/parsing/tokenizer/tokenizer_utils.c \
./src/parsing/tokenizer/modify_type_utils.c \
./src/parsing/tokenizer/set_redir_relations.c \
./src/parsing/tokenizer/env_to_matrix.c \
./src/extra/token_extra.c \
./src/parsing/expand_env/expand_valid_char.c \
./src/parsing/expand_env/expand_utilis.c \
./src/parsing/expand_env/expnad.c \
./src/builtins/token.c \
./src/error/error.c \
./src/builtins/env/env_comand.c \
./src/builtins/unset/unset.c \
./src/builtins/cd/cd.c \
./src/builtins/env/set_start_env.c \
./src/builtins/env/env.c \
./src/main.c \


# Object files
OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

# Libraries
LIB = ./libft/libft.a ./libft/libftprintf.a ./libft/get_next_line.a 

# Commands
AR = ar rcs
CC = cc
RM = rm -f
CAT = cat number.txt

# Output
NAME = minishell
OBJDIR = Objs

$(shell mkdir -p $(OBJDIR))


# Create object directory if it doesn't exist


$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(FLGS) -o $@ $<


# Main target
$(NAME): $(OBJS)
	cd libft && make compile && make
	$(CC) $(FLGS) $(OBJS) $(LIB) -lreadline -o $(NAME)
	@echo "╔══════════════════════════╗"
	@echo "║ ✅ Compiled Successfully!║"
	@echo "╚══════════════════════════╝"

# Compile all source files
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(FLGS) -o $@ $<

# Phony targets
.PHONY: all clean fclean re exec norm normi

all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)
	cd ./libft && make clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

exec:
	$(CC) -g $(FLGS) $(SRCS)

norm:
	yes y| python3 -m c_formatter_42 -c $(SRCS)

normi:
	norminette $(SRCS)
	cd ./libft && norminette

s:
	clear && make re && ./minishell
v:
	clear && make re && $(VAL) ./minishell
e:
	make re && env -i ./minishell
b:
	tmux \; split-window -h \; send-keys 'bash' C-m \; select-pane -t 1 \; send-keys 'make s' C-m \; setw synchronize-panes on
g:
	make re && gdb -tui ./minishell

t:
	make re && cd ./minishell_tester  && ./tester
