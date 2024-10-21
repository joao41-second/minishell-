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


t_env* new_node(char *s1)
{
	t_env *var;
	char *content; 

	var = (t_env*)ft_malloc(1*sizeof(t_env),NULL);
	content = getenv(s1);
	var->name =ft_strdup(s1);
	var->content = ft_strdup(content);
	//free(content);
	return (var);
}

void free_split(char **ok)
{
	int i;
	
	i = -1;
	while (ok[++i] != NULL)
	{
		ft_free(ok[i],NULL);
	}
	ft_free(ok,NULL);
}

void print_env(void *point)
{
	t_env get ;
	t_list_ *list;

	list = (t_list_*) point;
	if(list != NULL)
	{
		get = *((t_env*)list->content);
		ft_printf("%s====%s \n", get.name, get.content);
	}
}

void free_env(void *point)
{
	t_env get ;
	t_list_ *list;

	list = (t_list_*) point;
	if(list != NULL)
	{
		get = *((t_env*)list->content);
		ft_free(get.name,NULL);
		ft_free(get.content,NULL);
		ft_free(list->content,NULL);
	}
	
}

void free_list(t_list_ *list,void (*free_struct)(void*))
{
	t_list_ *temp; 
	list = ft_node_start(list);
	while (list != NULL)
	{
		temp = list->next;
		(free_struct)(list);
		if(list != NULL)
			ft_free(list,NULL);
		list = temp; 
	}

}


t_list_ *env_split(char **env)
{
	char **var;
	t_list_ *list;
	t_list_ *temp;
	t_env	*envs;
	int i;
	
	var = ft_split(env[0],'=');
	envs = new_node(var[0]); 
	list = ft_node_new(envs);
	free_split(var);
	i = 0;
	while(env[++i] != NULL)
	{ 
		var = ft_split(env[i],'=');
		envs = new_node(var[0]);
		temp = ft_node_new(envs);
		ft_node_add_front(&list ,temp);
		free_split(var);
	}
	list = ft_node_start(list);
	return (list);
}
