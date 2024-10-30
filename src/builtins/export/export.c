/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:05:55 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/25 15:17:56 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <strings.h>

void * get_index(void * pointer,void *index)
{
	static int size = 0;
	int *i;

	i = (int *)index;
	(void)pointer;
	if (size >= *i)
	{
		size = 0;
		return(pointer);
	}
	else
		size++;
	return (NULL);
}

t_list_ *get_list_index(t_list_ *list,int index)
{
	int *ints;
	t_list_ *node;
	
	node = NULL;
	ints = &index;
	if(index > ft_list_size(list))
		return (NULL);
    node = (t_list_ *)get_list(list, ints, get_index);
	return (node);
}

void organizer_list(t_list_ ** list)
{
	(void)list;
	while (1){}	

}



void export_print()
{
	printf("declare -x");
}

void export_add( t_list_ **list, t_env *var)
{
	t_list_ *node;

	*list = ft_node_end(*list);
	node =  ft_node_new((void *)var);
	ft_node_add_front(list,node);
	
 }

void ft_export(t_minis *mini)
{
	(void)mini;
	t_env *var;
	t_list_ *node;
	
	var = NULL;	
    node = get_list_index(mini->env, 5);
	//if(node != NULL)
	var = (t_env*)node->content;
	//printf("oio");
	printf("%s =%s\n",var->name,var->content);
}
