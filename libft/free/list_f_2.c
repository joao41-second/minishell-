/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_f_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:59:42 by jperpect          #+#    #+#             */
/*   Updated: 2024/10/17 12:06:06 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_and_list.h"

// void	ft_print_list(t_list_ *list, t_list_ *list_b)
// {
// 	char	ola[33];

// 	ft_printf(" \n--------start ----- \n");
// 	if (list != NULL)
// 		list = ft_node_start(list);
// 	if (list_b != NULL)
// 		list_b = ft_node_start(list_b);
// 	while (list != NULL)
// 	{
// 		ft_printf("a %d ", list->number);
// 		ft_str_btis(32, list->index, ola);
// 		ola[32] = '\0';
// 		ft_printf(" index  = %s ", ola);
// 		ft_printf("\n");
// 		list = list->next;
// 	}
// 	ft_printf("\n");
// 	while (list_b != NULL)
// 	{
// 		ft_printf("b %d ", list_b->number);
// 		ft_str_btis(32, list_b->index, ola);
// 		ola[32] = '\0';
// 		ft_printf(" index  = %s ", ola);
// 		ft_printf("\n");
// 		list_b = list_b->next;
// 	}
// 	ft_printf(" \n--------fim ----- \n");
// }

void	ft_node_add_inver(t_list_ **lst, t_list_ *new)
{
	t_list_	*temp;

	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	temp = *lst;
	temp->previous = new;
	*lst = new;
}

t_list_	*ft_node_end(t_list_ *list)
{
	if (list->next != NULL)
	{
		while (list != NULL)
		{
			if (list->next == NULL)
				break ;
			list = list->next;
		}
	}
	return (list);
}

int	ft_list_size(t_list_ *list)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		i++;
		list = list->next;
	}
	return (i);
}
