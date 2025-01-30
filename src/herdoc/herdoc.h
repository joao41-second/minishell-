/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:39:49 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/30 18:47:17 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HERDOC_H
#ifdef HERDOC_H

# include "../error/error.h"
# include "../parsing/tokenizer/tokenizer.h"
# include "../Pipex/pipex.h"
# include "../parsing/expand_env/expand.h"

int		check_end_herdoc(char *str, char end);

void	change_file(t_minis *mini, int set, char sete, t_token *name);

int		herdoc(t_minis *mini, int set, char *end);

int		redirect_for_add_file(t_minis *mini, t_token *name);

int		redirect_for_new_file(t_minis *mini,t_token *name);

char	*expand_heradoc(t_minis *mini, char *str);

void	set_redir(t_list_ *list, t_btree **btree);

void	redirect_(t_list_ *list,t_minis *mini);

void	redirect_bil(t_list_ *list,t_minis *mini);

void	dell_redir( t_list_ **list);

#endif // !HERDOC_H
