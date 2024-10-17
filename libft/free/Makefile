# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 14:51:15 by jperpect          #+#    #+#              #
#    Updated: 2024/10/17 12:04:23 by jperpct          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLGS = -Wall -Wextra -Werror

NAME =	free_and_list.a

AR = ar rcs

SRCS = list_f.c list_f_2.c ft_free.c


OBJECT = $(SRCS:.c=.o) 


CC = cc 

RM = rm -f


COUNT_FILE = count.txt

# Verifica se o arquivo existe; se não, cria com valor inicial 0
ifeq ($(wildcard $(COUNT_FILE)),)
    $(shell echo 0 > $(COUNT_FILE))
endif

COUNT = $(shell cat $(COUNT_FILE))


#.SILENT:

all: $(NAME)

$(NAME): $(OBJECT)

	@$(AR) $@ $^
	@rm -f $(COUNT_FILE)

%.o:%.c list_and_free.a
	@cc -c $(FLGS) -o $(LIB) $@ $< 
	$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
	@echo $(COUNT) > $(COUNT_FILE)
	@$(MAKE) -s show_progress

	

show_progress:
	@clear

	@PERCENT=$$(($(COUNT) * 100 / $(words $(SRCS)) )); \
	PROG_LEN=$$(($$PERCENT / 10)); \
	echo -n "  $(NAME) ["; \
	for i in `seq 1 $$PROG_LEN`; do \
		echo -n "#"; \
	done; \
	for i in `seq $$PROG_LEN 10`; do \
		echo -n " "; \
	done; \
	echo "] $$PERCENT%"



clean:
	$(RM) $(OBJECT)
	@rm -f $(COUNT_FILE)
fclean: clean
	$(RM) $(NAME)
	@rm -f $(COUNT_FILE) 

re: fclean all

exec:
	cc	-g   $(SRCS) $(BONUS) -lbsd

# norm: 
#    yes y|	python3 -m c_formatter_42 -c $(BONUS)
