/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:05:55 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/04 13:12:31 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

void swap_env(t_list_ **node1,t_list_ **node2)
{
	t_env *nod1;
	t_env *nod2;
	char *save;

	nod1 = (t_env*)(*node1)->content;
	nod2 = (t_env*)(*node2)->content;
	save = nod1->name;
	nod1->name = nod2->name;
	nod2->name = save;
	save = nod1->content;
	nod1->content = nod2->content;
	nod2->content = save;
}

int env_char_max(t_list_ *list,int len)
{
	int i;
	t_env *node;
	t_list_ *chek;
	int len_max;

	len_max = 0;
	i = -1;
	while (++i < len) 
	{
		chek = get_list_index(list,i);
		if(chek == NULL)
			break;
		node = chek->content;
		if(ft_strlen(node->name) > (size_t)len_max)
		 len_max = ft_strlen(node->name);
	}
	return(len_max);
}

void print_export(void *point)
{
	t_env get ;
	t_list_ *list;

	list = (t_list_*) point;
	if(list != NULL  )
	{
		get = *((t_env*)list->content);
		if(get.content != NULL)
			printf("declare -x %s=\"%s\" \n", get.name, get.content);
		else if(get.content == NULL)
		{
			printf("declare -x %s\n",get.name);
		}
	}
}

void org_nex(t_list_ *list,int *i,int *set,int char_max)
{
	t_list_ *nod1;
	t_list_ *nod2;

	nod1 = get_list_index(list,*i);
	nod2 = get_list_index(list,*i+1);

	if(nod1 != NULL && nod2 != NULL) 
	{
		if(ft_strncmp(list_to_env(nod1)->name,list_to_env(nod2)->name ,char_max ) > 0)
		{
			swap_env(&nod1,&nod2);
			*set =1;
		}
	}

}

void organizer_list(t_list_ *list)
{
	int len;
	int char_max;
	int set;
	int i;

	len = ft_list_size(list);
	char_max = env_char_max(list, len);
	i = 0;
	set = 0;

	while(i++ <= len)
	{
		org_nex(list, &i, &set,char_max);
		if(i >= len && set == 1)
		{
			i = -1;
			set = 0;
		}
	}
	list = ft_node_start(list);
	 print_list(list,print_export);
}

void ft_export(t_minis *mini)
{
	char **export;
	t_env *env;

	if(mini->split[1]!= NULL)
	{
		env = ft_malloc(1*sizeof(t_env),NULL);
		export = ft_split(mini->split[1],'=');
		env->name= ft_strdup(export[0]);
		if(export[1] != NULL)
			env->content = 	ft_strjoin("",&mini->split[1][strlen(export[0])+1]);
		else
			env->content = NULL;
		free_split(export); 
		export_add(&mini->env,env);
		export_add(&mini->env_org, env);
	}
	if(mini->split[1]== NULL)
		organizer_list(mini->env_org);
}
