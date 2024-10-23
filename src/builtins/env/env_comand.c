/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_comand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:08:21 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/22 14:59:44 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void* get_env(void *point ,void *locate)
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
			return (get.content);
		}
	}
	return (NULL);
}


void ft_env(t_minis *mini)
{
	print_list(mini->env,print_env);
}

char *ft_getenv(t_minis *mini ,char *var)
{
	return ((char *)get_list(mini->env,var,get_env));
}
