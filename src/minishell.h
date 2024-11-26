/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:46:57 by jperpect          #+#    #+#             */
/*   Updated: 2024/11/26 18:06:43 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINISHELL_H
#ifdef MINISHELL_H

# include "../libft/Get_next_line/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"
# include "parsing/tokenizer/tokenizer.h"
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
# include "./Pipex/pipex.h"

int			check_syntax(const char *str);

void		free_split(char **ok);

void		free_list(t_list_ *list, void (*free_struct)(void *));

char		**env_to_matrix(t_minis *mini);

t_list_		*tokenizeAndCheckBashCommand(t_minis *mini);

void		set_redirection_relations(t_list_ *list);

int			is_whitespace(char c);

int			is_quote(char c);

t_token		*create_token(char *str, char *type);

void		add_to_list(t_list_ **list, t_token *token);

char		*get_redirection_type(char *str);

void		free_env_matrix(char **env_matrix);

int			extract_quoted_string(char *line, int *i, char **token);

int			is_quoted_string_command(char *str, char **env_matrix);

void		modify_token_types(t_list_ *token_list, t_minis *mini);


#endif
