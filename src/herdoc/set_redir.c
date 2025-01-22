/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:31:40 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/22 19:27:30 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	relink_list(t_list_ **list,void *content)
{
	t_list_ *new;

	new = ft_node_new(content);

	*list = ft_node_end(*list);
	ft_node_add_front(list, new);
}

void set_redir(t_list_ *list, t_btree **btree)
{
	t_list_ *list_redir;
	t_btree *save;

	save = *btree;
	list_redir = NULL;
	while(list != NULL)
	{
		if (ft_strncmp(get_token(list)->type,"redir",10) == 0)
		{
			if(list_redir == NULL)
				list_redir = ft_node_new(list->content);
			else
				relink_list(&list_redir, list->content);
		}	
		if (ft_strncmp(get_token(list)->type,"pipe",10) == 0 || list->next == NULL)
		{
			if(ft_strncmp((char *)(*btree)->left->cmd, "|", 10) != 0)
			{
				(*btree)->left->redir = list_redir;
				
				list_redir = NULL;
				print_token_list((*btree)->left->redir);
				(*btree) = (*btree)->right;
			}
		}
		list = list->next;
	}
	(*btree) = save;
}
