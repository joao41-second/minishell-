# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 06:17:31 by jperpect          #+#    #+#              #
#    Updated: 2024/10/15 14:12:25 by rpires-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler flags
# FLGS = -Wall -Wextra -Werror -lreadline

# Make flags
MAKEFLAGS += -s

# Source files
SRCS = $(shell find src -name '*.c')

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
NAME = so_long
OBJDIR = Objs

# Create object directory if it doesn't exist
$(shell mkdir -p $(OBJDIR))

# Main target
$(NAME): $(OBJS)
	cd libft && make compile && make
	$(CC) $(FLGS) $(OBJS) $(LIB) -o $(NAME)
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