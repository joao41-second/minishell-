# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 14:51:15 by jperpect          #+#    #+#              #
#    Updated: 2024/08/19 11:56:18 by jperpect         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLGS = -Wall -Wextra -Werror

NAME =get_next_line.a

AR = ar rcs

SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c
 

OBJECT = $(SRCS:.c=.o) 


CC = cc 

RM = rm -f


COUNT_FILE = count.txt

# Verifica se o arquivo existe; se não, cria com valor inicial 0
ifeq ($(wildcard $(COUNT_FILE)),)
    $(shell echo 0 > $(COUNT_FILE))
endif


 #.SILENT:

all: $(NAME)

$(NAME): $(OBJECT)
	$(AR) $@ $^
		@rm -f $(COUNT_FILE)



%.o:%.c 
	cc -c $(FLGS) -o $@ $<



clean:
	$(RM) $(OBJECT)
		@rm -f $(COUNT_FILE)


fclean: clean
	$(RM) $(NAME) 
	@rm -f $(COUNT_FILE)

re: fclean all

exec:
	cc	-g   $(SRCS) $(BONUS) -lbsd
		@rm -f $(COUNT_FILE)


# norm: 
#    yes y|	python3 -m c_formatter_42 -c $(BONUS)