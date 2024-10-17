# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 11:50:39 by jperpect          #+#    #+#              #
#    Updated: 2024/07/24 11:04:59 by jperpect         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLGS = -Wall -Wextra -Werror

AR = ar rcs

LIBFT_DIR = libft
PRINTF_DIR = printf
Get_next_line_DIR = Get_next_line
Free_DIR = free

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
Get_next_line = $(Get_next_line_DIR)/get_next_line.a
Free = $(Free_DIR)/free_and_list.a
SRCS = libft.a libftprintf.a get_next_line.a free_and_list.a

RM = rm -f

.SILENT:

all: $(SRCS)

$(SRCS):
	@cd $(LIBFT_DIR) && make 
	@mv $(LIBFT) .
	@cd $(PRINTF_DIR) && make 
	@mv $(PRINTF) .
	@cd $(Get_next_line_DIR) && make 
	@mv $(Get_next_line) .
	@cd $(Free_DIR) && make 
	@mv $(Free) .
	
	$(AR) $@ $^ 
clean:
	$(RM) $(SRCS)
	@cd $(LIBFT_DIR) && make clean
	@cd $(PRINTF_DIR) && make clean 
	@cd $(Free_DIR) && make clean
	@cd $(Get_next_line_DIR) && make clean

compile:
	@cd $(LIBFT_DIR) && make 
	@mv $(LIBFT) .
	@cd $(PRINTF_DIR) && make
	@mv $(PRINTF) .
	@cd $(Get_next_line_DIR) && make
	@mv $(Get_next_line) .
	@cd $(Free_DIR) && make
	@mv $(Free) .



fclean: clean
	$(RM) $(SRCS)
	
re: fclean all

