/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:06:26 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/04 15:49:33 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	*get_env_node(void *point, void *locate)
{
	t_env	get;
	t_list_	*list;
	char	*loc;

	loc = (char *)locate;
	list = (t_list_ *)point;
	if (list != NULL)
	{
		get = *((t_env *)list->content);
		if (ft_strncmp(get.name, loc, ft_strlen(loc)) == 0)
		{
			return (point);
		}
	}
	return (NULL);
}

void unset_list(t_list_ **list,char *str)
{
	t_list_	*ok;
	
	if (*list == NULL)
		return ;
	ok = *list;
	ok = ft_node_start(ok);
	ok = (t_list_ *)get_list(*list , str, get_env_node);
	if (ok == NULL)
		return ;
	ft_free_node(&ok, free_env);
	ok = ft_node_start(ok);
	*list = ok;

}

void	ft_unset(t_minis *mini)
{
	unset_list(&mini->env, mini->split[1]);
	unset_list(&mini->env_org, mini->split[1]);
}

