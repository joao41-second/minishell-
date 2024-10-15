/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:46:23 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/15 19:18:29 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


t_env* new_node(char *s1, char *s2)
{
	t_env var;

	var.name = s1;
	var.content = s2;
	return (&var);
}

t_list_ *env_split(char **env)
{
	char **var;
	t_list_ *list;
	int i;
	
	var = ft_split(env[0],'=');
	list = ft_node_new((void *)new_node(var[0],var[1]));
	i = 0;
	while(env[++i] != NULL)
	{
		var = ft_split(env[i],'=');
		ft_node_add_front(&list ,ft_node_new(new_node(var[0],var[1])));
	}
	return (list);
}
