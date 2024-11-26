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

void	*get_env_content(void *point, void *locate)
{
	t_env	get;
	t_list_	*list;
	char	*loc;

	loc = (char *)locate;
	list = (t_list_ *)point;
	if (list != NULL)
	{
		get = *((t_env *)list->content);
		if (ft_strncmp(get.name, loc, ft_strlen(loc) + 10) == 0)
		{
			return (list->content);
		}
	}
	return (NULL);
}


t_env *ft_getenv_content(t_list_ *list,char *var)
{
	t_env	*env;
	env = (t_env *) get_list(list, var, get_env_content);
	return (env);
}
