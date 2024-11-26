/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:05:55 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/26 17:33:18 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>


void	ft_export_add( t_list_ *list, char *str, t_minis *mini)
{
	t_env	*env;
	char	**export;
	char	*temp;
	export = ft_split(str, '=');
	
	if (str[ft_strlen(export[0])-1] == '+')
	{
		temp = ft_substr(export[0], 0, ft_strlen(export[0])-1);
		ft_free(export[0],NULL);
		export[0] = temp;
		temp = NULL;
	}
	if(ft_getenv_content(list, export[0]) != NULL){

		env = ft_getenv_content(list, export[0]);
		env->chek = TRUE;
		if(export[1] != NULL && str[ft_strlen(export[0])-1] != '+')
			ft_free(env->content,NULL);
	}
	else
	{
		env = ft_malloc(1 * sizeof(t_env), NULL);
		env->content = NULL;
	}
	env->name = ft_strdup(export[0]);
	if (export[1] != NULL  && str[ft_strlen(export[0])-1] != '+' )
		env->content = ft_strjoin("",
				&mini->split[1][strlen(export[0]) + 1]);
	else if (str[ft_strlen(export[0])] == '=' && str[ft_strlen(export[0])-1] != '+' )
	{
		temp = ft_malloc(1 * sizeof(char), NULL);
		temp[0] = '\0';
		env->content = temp;
	}
	else if (export[1] != NULL  && str[ft_strlen(export[0])-1] == '+')
	{
		temp = ft_strjoin(env->content,ft_strjoin("",
				&mini->split[1][strlen(export[0]) + 1]));
		ft_free(env->content,NULL);
		env->content = temp;
	}
	
	if(ft_getenv_content(list, export[0]) == NULL)
		export_add(&list, env);
	free_split(export);
}

void	ft_export(t_minis *mini)
{
	if (mini->split[1] != NULL)
	{
		ft_export_add(mini->env, mini->split[1], mini);
		ft_export_add(mini->env_org, mini->split[1], mini);
	}
	if (mini->split[1] == NULL)
		organizer_list(mini->env_org);
}
