/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:39:19 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/04 12:53:28 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <strings.h>

void	export_add( t_list_ **list, t_env *var)
{
	t_list_	*node;

	*list = ft_node_end(*list);
	node = ft_node_new((void *)var);
	ft_node_add_front(list, node);
}

t_env	*list_to_env(t_list_ *list)
{
	t_env	*ret;

	ret = NULL;
	if (list != NULL)
		ret = (t_env *)list->content;
	return (ret);
}
