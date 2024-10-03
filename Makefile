# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 06:17:31 by jperpect          #+#    #+#              #
#    Updated: 2024/09/10 13:10:45 by jperpect         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLGS = -Wall -Wextra -Werror

MAKEFLAGS += -s

FILES = ./src/main.c ./src/free/ft_free.c ./src/free/list_f.c


SRCS = $(FILES:.c=.o)
BON = $(BONUS:.c=.o)

LIB = ./libft/libft.a ./libft/libftprintf.a ./libft/get_next_line.a 



AR = ar rcs

CC = cc 

RM = rm -f

CAT = cat number.txt 

NAME = so_long

# Verifica se o arquivo existe; se não, cria com valor inicial 0



COUNT = $(shell cat $(COUNT_FILE))


#.SILENT:

$(NAME) : $(MINIX) $(SRCS)
	cd libft && make compile && make 
	cc $(FLGS) $(SRCS) $(LIB) -o $(NAME)
	echo "╔══════════════════════════╗"
	echo "║ ✅ Compiled Successfully!║"
	echo "╚══════════════════════════╝"
	@rm -f $(COUNT_FILE)


all: $(NAME) $(BONUS)
%.o:%.c 
	@cc -c $(FLGS) -o $@ $< 



bonus:$(BON)
	cd libft && make compile && make 
	
	cc $(FLGS) $(BONUS) $(LIB)  -o $(NAME)
	echo "╔══════════════════════════╗"
	echo "║ ✅ Compiled Successfully!║"
	echo "╚══════════════════════════╝"
	@rm -f $(COUNT_FILE)
	

clean: $(fclean)
	$(RM)  $(SRCS)
	$(RM)  $(BON)
	$(RM)  $(OBJS_CLI)
	cd ./libft && make clean
		@rm -f $(COUNT_FILE)
fclean: $(clean)
	$(RM) $(NAME)
	@rm -f $(COUNT_FILE)
	make clean


re: fclean all

exec:
	cc	-g $(FLGS)  $(SRCS) $(BONUS) -lbsd
		@rm -f $(COUNT_FILE)

norm: 
	 yes y|	python3 -m c_formatter_42 -c $(FILES)
		@rm -f $(COUNT_FILE)

normi:
	norminette $(FILES)
	norminette $(BONUS)
	cd ./libft && norminette
		@rm -f $(COUNT_FILE)
	


