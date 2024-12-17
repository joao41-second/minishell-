/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:06:33 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/28 14:35:02 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

t_list_	*list_env_i(void)
{
	t_env	*vars;
	char	cwd[PATH_MAX];
	t_list_	*list;
	t_list_	*l2;

	vars = ft_malloc(6 * sizeof(t_env), NULL);
	vars[0].name = "OLDPWD";
	vars[0].content = NULL;
	vars[1].name = "PWD";
	vars[1].content = getcwd(cwd, sizeof(cwd));
	vars[2].name = "SHLVL";
	vars[2].content = "1";
	vars[3].name = "_";
	vars[3].content = "/usr/bin/env";
	list = ft_node_new((void *)&vars[0]);
	l2 = ft_node_new(&vars[1]);
	ft_node_add_front(&list, l2);
	l2 = ft_node_new(&vars[2]);
	ft_node_add_front(&list, l2);
	l2 = ft_node_new(&vars[3]);
	ft_node_add_front(&list, l2);
	ft_node_add_front(&list,ft_node_new( (void *) new_node_une("?","0")));
	return (list);
}
