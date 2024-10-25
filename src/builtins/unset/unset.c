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

void	ft_free_node(t_list_ **list, void (*free_struct)(void*))
{
	t_list_	*temp;
	t_list_	*priv;
	t_list_	*next;

	if(list != NULL)
	{	
		(free_struct)(*list);
		temp = *list;
		priv = temp->previous;
		next = temp->next;
		if(next != NULL)
			next->previous = priv; 
		if(priv != NULL)
			priv->next = next;

		if(priv != NULL && next != NULL)
			ft_free(*list,NULL);
		if(next != NULL)
			*list= next;
		else if(priv != NULL)
			*list= priv;
	}
}

void ft_unset(t_minis *mini)
{
	t_list_ *ok;
	
	ok = mini->env;
    ok = (t_list_ *) get_list(mini->env,"TMUX_CONF",get_env_node);
	if(ok == NULL)
		return ;
	ft_free_node(&ok,free_env);
	ok = ft_node_start(ok); 
	
	mini->env = ok;
	//ft_env(mini);
	//rint_list(ok,print_env);

}
