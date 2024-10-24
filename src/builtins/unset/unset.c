/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:06:26 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/24 15:09:16 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void* get_env_node(void *point ,void *locate)
{
	t_env get ;
	t_list_ *list;
	char *loc;
	
	loc = (char *)locate;
	list = (t_list_*) point;
	if(list != NULL)
	{
		get = *((t_env*)list->content);
		if(ft_strncmp(get.name,loc,ft_strlen(loc)) == 0)
		{
			return (point);
		}
	}
	return (NULL);
}



ft_unset(t_minis *mini)
{
	mini->env = (t_list_ *) get_list(mini->env,"OLDPWD",get_env_node);

	//ft_free_node(&mini->env,free_env);
	//mini->env = ft_start_node(mini->env); 
	//ft_env(mini->env);
}
