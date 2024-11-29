/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:33:39 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/29 14:24:24 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_and_list.h" 

void	*ft_malloc(size_t size, void *list_set)
{
	t_list_			*new;
	static t_list_	*list;
	void			*mal;

	if (ft_maolloc_next(list_set, list, size) != NULL)
	{
		list = ft_maolloc_next(list_set, list, size);
		return (NULL);
	}
	mal = malloc(size);
	if (mal == NULL)
	{
		ft_free_all(NULL);
		write(2, "error_remove_the_limited_memory_bitch\n", 39);
		exit(1);
	}
	new = ft_node_new_free(mal);
	if (new == NULL)
	{
		ft_free_all(NULL);
		write(2, "error_remove_the_limited_memory_bitch\n", 39);
		exit(1);
	}
	ft_node_add_front(&list, new);
	return (new->content);
}

void	ft_free_all(void *list_set)
{
	static t_list_	*list = NULL;
	t_list_			*temp;

	if (list == NULL && list_set != NULL)
	{
		list = list_set;
		return ;
	}
	list = ft_node_start(list);
	while (list != NULL)
	{
		temp = list->next;
		if (list->content != NULL)
			free(list->content);
		free(list);
		list = temp;
	}
}

void	ft_free(void *var, void *list_set)
{
	static t_list_	*list;
	t_list_			*temp;

	if (list == NULL && list_set != NULL)
	{
		list = list_set;
		return ;
	}
	temp = list;
	while (list != NULL)
	{
		if (list->content == var)
		{
			free(list->content);
			list->content = NULL;
			var = NULL;
			list = free_next(list);
			break ;
		}
		list = list->next;
	}
	list = temp;
}

void	start_alloc(void)
{
	t_list_	*list;

	list = ft_node_new_free(malloc(sizeof(t_list_)));
	ft_malloc(3, list);
	ft_free_all(list);
	ft_free(NULL, list);
}
