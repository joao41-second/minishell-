/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:39:49 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/02 13:41:25 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HERDOC_H
#ifdef HERDOC_H

void	change_file(t_minis *mini, int set, char sete, t_token *name);

void	herdoc(t_minis *mini, int set, char *end);

int		redirect_for_add_file(t_minis *mini, t_token *name);

int		redirect_for_new_file(t_minis *mini,t_token *name);

char	*expand_heradoc(t_minis *mini, char *str);

#endif // !HERDOC_H
