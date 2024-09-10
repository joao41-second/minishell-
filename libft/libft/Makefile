# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 06:17:31 by jperpect          #+#    #+#              #
#    Updated: 2024/08/16 15:04:41 by jperpect         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLGS = -Wall -Wextra -Werror

NAME = libft.a

AR = ar rcs

SRCS = ft_atoi.c ft_isdigit.c ft_memmove.c ft_split.c ft_strlcat.c ft_strrchr.c \
 ft_bzero.c ft_isprint.c ft_memset.c ft_strlcpy.c ft_strtrim.c \
 ft_calloc.c ft_itoa.c ft_putchar_fd.c ft_strchr.c ft_strlen.c ft_substr.c \
 ft_isalnum.c ft_memchr.c ft_putendl_fd.c ft_strdup.c ft_strmapi.c ft_tolower.c \
 ft_isalpha.c ft_memcmp.c ft_putnbr_fd.c ft_striteri.c ft_strncmp.c ft_toupper.c \
 ft_isascii.c ft_memcpy.c ft_putstr_fd.c ft_strjoin.c ft_strnstr.c ft_str_btis.c ft_atol.c \
 ft_verfic_char_list.c


BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		ft_lstlast.c ft_lstadd_back.c  ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstprint.c\

OBJECT = $(SRCS:.c=.o) 

OBJECT_B = $(BONUS:.c=.o)

CC = cc 

RM = rm -f

COUNT_FILE = count.txt

# Verifica se o arquivo existe; se não, cria com valor inicial 0
ifeq ($(wildcard $(COUNT_FILE)),)
    $(shell echo 0 > $(COUNT_FILE))
endif

COUNT = $(shell cat $(COUNT_FILE))



.SILENT:

all: $(NAME)

$(NAME): $(OBJECT)
	@$(AR) $@ $^
	@rm -f $(COUNT_FILE)

bonus: $(OBJECT_B) $(NAME)
	@ar rcs $(NAME) $^
	@rm -f $(COUNT_FILE)


%.o:%.c libft.h
	@cc -c $(FLGS) -o $@ $< 
	$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))

	# Salva o novo valor de COUNT no arquivo
	@$(MAKE) show_progress
	@echo $(COUNT) > $(COUNT_FILE)


show_progress:
	@clear

	@PERCENT=$$(($(COUNT) * 100 / $(words $(SRCS)))); \
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
	$(RM)  $(OBJECT) $(OBJECT_B)
		@rm -f $(COUNT_FILE)

fclean: clean
	$(RM) $(NAME)
		@rm -f $(COUNT_FILE)

re: fclean all

exec:
	cc	-g $(FLGS)  $(SRCS) $(BONUS) -lbsd
		@rm -f $(COUNT_FILE)

norm: 
	yes y | python3 -m c_formatter_42 -c $(SRCS)
		@rm -f $(COUNT_FILE)