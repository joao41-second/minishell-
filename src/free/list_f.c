/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:04:01 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/12 10:55:28 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

t_free	*ft_node_new(void * n)
{
	t_free	*new_node;

	new_node = (t_free *)malloc(1 * (sizeof(t_free)));
	if (new_node == NULL)
		return (NULL);
	new_node->content = n;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

void	ft_node_add_front(t_free **lst, t_free *new)
{
	t_free	*temp;

	if (lst == NULL || new == NULL)
		return ;
	new->previous = *lst;
	temp = *lst;
	temp->next = new;
	*lst = new;
}

void	*ft_node_clear(t_free *tes)
{
	t_free	*temp;

	tes = ft_node_start(tes);
	while (tes != NULL)
	{
		temp = tes->next;
		free(tes);
		tes = temp;
	}
	return (NULL);
}

t_free	*ft_node_start(t_free *list)
{
	if (list->previous != NULL)
	{
		while (list != NULL)
		{
			if (list->previous == NULL)
				break ;
			list = list->previous;
		}
	}
	return (list);
}

/*
t_free	*ft_new_list_null(t_free *list, int len)
{
	t_free	*new;
	int			i;
	int			env;

	env = 0;
	i = 0;
	list = ft_node_new((void*)env);
	while (++i < len)
	{
		new = ft_node_new((void*)env);
		ft_node_add_front(&list, new);
	}
	return (list);
}


 */

// int	main(int ac,char **av)
// {
// 		t_free *tes;
// 		t_free *tea;
// 		t_free *teb;
// 		t_free *tec;
// 		tes = ft_node_new(1561,0);
// 		tea = ft_node_new(1,1);
// 		teb = ft_node_new(15,2);
// 		tec = ft_node_new(18,3);

// 		ft_node_add_front(&tes,tea);
// 		ft_node_add_front(&tes,teb);
// 	ft_node_add_front(&tes,tec);

// 	while(tes != NULL)
// 	{
// 		ft_printf("%d\n",tes->content);
// 		ft_printf("antes %x\n",tes->previous);
// 		ft_printf("depois %x\n",tes->next);
// 		if(tes->next == NULL)
// 			break ;
// 		tes = tes->next;
// 	}

// 	while(tes != NULL)
// 	{
// 		ft_printf("%d\n",tes->content);

// 		if(tes->previous == NULL)
// 			break ;
// 		tes = tes->previous;
// 	}

// }
