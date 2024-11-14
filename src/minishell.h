/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:46:57 by jperpect          #+#    #+#             */
/*   Updated: 2024/11/14 14:52:15 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINISHELL_H
#ifdef MINISHELL_H

# include "../libft/Get_next_line/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"
//#include "../libft/free/free_and_list.h"
//#include "../libft/free/list.h"
//#include "./comands_line/readline.h"
# include "../libft/libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_mines
{
	t_list_	*env;
	t_list_	*env_org;
	char	path[PATH_MAX];
	char	*line;
	char	**split;
	int		comand;
	int		exit_code_error;
}			t_minis;
# include "./builtins/builtins.h"
# include "./comands_line/readline.h"

int			check_syntax(const char *str);

void		free_split(char **ok);

void		free_list(t_list_ *list, void (*free_struct)(void *));

#endif
