/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:46:57 by jperpect          #+#    #+#             */
/*   Updated: 2024/10/15 19:33:15 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINISHELL_H
#ifdef MINISHELL_H

#include "../libft/Get_next_line/get_next_line_bonus.h"
#include "../libft/printf/ft_printf.h"
#include "./comands_line/readline.h"
#include "./free/free.h"
#include "../libft/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_env {
	char* name;
	char* content;
} t_env;

typedef struct s_mines {
 t_list_ *env;
} t_minis;

t_list_ *env_split(char **env);

void print_list(t_list_ *list,void(*print)(void*));

void print_env(void *point);



#endif 
