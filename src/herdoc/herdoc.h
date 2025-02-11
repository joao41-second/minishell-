/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:39:49 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/10 16:09:48 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HERDOC_H
#ifdef HERDOC_H

# define HER "/tmp/her"

void	change_file(t_minis *mini, int set, char sete, t_token *name);

void		herdoc(t_minis *mini, int set, char *end);

int		redirect_for_add_file(t_minis *mini, t_token *name);

int		redirect_for_new_file(t_minis *mini, t_token *name);

char	*expand_heradoc(t_minis *mini, char *str);

void	set_redir(t_list_ *list, t_btree **btree, t_minis *mini);

void	redirect_(t_list_ *list, t_minis *mini);

void	redirect_bil(t_list_ *list, t_minis *mini);

void	dell_redir(t_list_ **list);

void	set_redir_(int fd, int nb, int on);

void	ser_fd(int nb);
#endif // !HERDOC_H
