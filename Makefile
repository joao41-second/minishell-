# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 06:17:31 by jperpect          #+#    #+#              #
#    Updated: 2024/10/15 13:42:13 by rpires-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FLGS = -Wall -Wextra -Werror -lreadline
MAKEFLAGS += -s
FILES = ./src/main.c ./src/free/ft_free.c ./src/free/list_f.c
SRCS = $(FILES:.c=.o)
BON = $(BONUS:.c=.o)
LIB = ./libft/libft.a ./libft/libftprintf.a ./libft/get_next_line.a
AR = ar rcs
CC = cc
RM = rm -f
CAT = cat number.txt
NAME = minishell
OBJDIR = Objs
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS)))
BON_OBJS = $(addprefix $(OBJDIR)/, $(notdir $(BON)))

# Create object directory if it doesn't exist
$(shell mkdir -p $(OBJDIR))

# Verifica se o arquivo existe; se não, cria com valor inicial 0
COUNT = $(shell cat $(COUNT_FILE))

$(NAME): $(MINIX) $(OBJS)
	cd libft && make compile && make
	$(CC) $(FLGS) $(OBJS) $(LIB) -o $(NAME)
	@echo "╔══════════════════════════╗"
	@echo "║ ✅ Compiled Successfully!║"
	@echo "╚══════════════════════════╝"
	@rm -f $(COUNT_FILE)

all: $(NAME) $(BONUS)

$(OBJDIR)/%.o: ./src/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(FLGS) -o $@ $<

$(OBJDIR)/%.o: ./src/free/%.c
	@$(CC) -c $(FLGS) -o $@ $<

bonus: $(BON_OBJS)
	cd libft && make compile && make
	$(CC) $(FLGS) $(BON_OBJS) $(LIB) -o $(NAME)
	@echo "╔══════════════════════════╗"
	@echo "║ ✅ Compiled Successfully!║"
	@echo "╚══════════════════════════╝"
	@rm -f $(COUNT_FILE)

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(OBJS_CLI)
	cd ./libft && make clean
	@rm -f $(COUNT_FILE)

fclean: clean
	$(RM) $(NAME)
	@rm -f $(COUNT_FILE)

re: fclean all

exec:
	$(CC) -g $(FLGS) $(SRCS) $(BONUS) -lbsd
	@rm -f $(COUNT_FILE)

norm:
	yes y| python3 -m c_formatter_42 -c $(FILES)
	@rm -f $(COUNT_FILE)

normi:
	norminette $(FILES)
	norminette $(BONUS)
	cd ./libft && norminette
	@rm -f $(COUNT_FILE)

.PHONY: all bonus clean fclean re exec norm normi
