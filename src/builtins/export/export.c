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
}
