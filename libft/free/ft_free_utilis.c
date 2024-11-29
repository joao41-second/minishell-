/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:16:04 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/29 14:27:19 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./free_and_list.h"

t_list_	*ft_maolloc_next(t_list_ *list_set, t_list_ *list, size_t size)
{
	if (list_set != NULL && size == 134)
	{
		list = list_set;
		return (list);
	}
	if (list_set != NULL && list == NULL)
	{
		list = list_set;
		return (list);
	}
	if (list == NULL)
	{
		write(2, "error\n", 7);
	}
	return (NULL);
}

t_list_	*ft_node_new_free(void *n)
{
	t_list_	*new_node;

	new_node = (t_list_ *)malloc(1 * sizeof(t_list_));
	if (new_node == NULL)
		return (NULL);
	new_node->content = n;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

void	ft_remove(t_list_ **node)
{
	t_list_	*prv;
	t_list_	*temp;

	temp = *node;
	prv = temp->previous;
	prv->next = NULL;
	free(*node);
	*node = prv;
}

void	ft_emove(t_list_ **node)
{
	t_list_	*prv;
	t_list_	*nex;
	t_list_	*temp;

	temp = *node;
	nex = temp->next;
	prv = temp->previous;
	nex->previous = prv;
	prv->next = nex;
	free(*node);
	*node = prv;
}

t_list_	*free_next(t_list_ *list)
{
	if (list->next == NULL )
	{
		ft_remove(&list);
		ft_malloc(134, list);
	}
	else if (list->next != NULL && list->previous != NULL)
		ft_emove(&list);
	return (list);
}
