/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:30:04 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/24 14:30:04 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_and_list.h"


void free_list(t_list_ *list,void (*free_struct)(void*))
{
	t_list_ *temp; 
	list = ft_node_start(list);
	while (list != NULL)
	{
		temp = list->next;
		(free_struct)(list);
		if(list != NULL)
			ft_free(list,NULL);
		list = temp; 
	}

}

void	ft_free_node(t_list_ **list, void (*free_struct)(void*))
{
	t_list_	*temp;
	t_list_	*priv;
	t_list_	*next;

	(free_struct)(list);
	temp = *list;
	priv = temp->previous;
	next = temp->next;
	ft_free(*list,NULL);
	priv->next = next;
	next->previous = priv;
	*list= priv;
}
