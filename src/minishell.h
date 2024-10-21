/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:46:57 by jperpect          #+#    #+#             */
/*   Updated: 2024/10/21 16:08:48 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINISHELL_H
#ifdef MINISHELL_H

#include "./builtins/builtins.h"
#include "../libft/Get_next_line/get_next_line_bonus.h"
#include "../libft/printf/ft_printf.h"
//#include "../libft/free/free_and_list.h"
//#include "../libft/free/list.h"
//#include "./comands_line/readline.h"
#include "../libft/libft/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>


typedef struct s_mines {
 t_list_ *env;
} t_minis;


int		check_syntax(char *str);



void free_list(t_list_ *list,void (*free_struct)(void*));

#endif 
