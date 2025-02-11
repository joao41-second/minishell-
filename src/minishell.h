/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:46:57 by jperpect          #+#    #+#             */
/*   Updated: 2025/02/11 16:01:25 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINISHELL_H
#ifdef MINISHELL_H

# define TRUE 0
# define FALSE 1

# include "../libft/Get_next_line/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"
//#include "../libft/free/free_and_list.h"
//#include "../libft/free/list.h"
//#include "./comands_line/readline.h"
# include "../libft/libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <asm-generic/errno.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "minis.h"
# include "./error/error.h"
# include "./parsing/expand_env/expand.h"
# include "./builtins/builtins.h"
# include "./Pipex/pipex.h"
# include "./comands_line/readline.h"
# include "parsing/tokenizer/tokenizer.h"
# include "./herdoc/herdoc.h"

int			check_syntax(const char *str);

void		free_split(char **ok);

void		free_list(t_list_ *list, void (*free_struct)(void *));

t_btree		*token_merger(t_minis *mini);

void		and_shelvl(t_minis *mini);

void		token_comand_set_start(t_list_ **list);

int			chek_comand_exit(t_list_ **list);

void		set_new_comand(t_list_ **list);

int			chek_biltin(char **cmd);
#endif
