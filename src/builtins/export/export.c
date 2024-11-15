/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:05:55 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/15 15:22:14 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
t_env	*set_pwd(t_env *env, char *str, t_minis *mini)
{
	if (str != NULL)
	{
		if (ft_strncmp(str, "PWD", 5) == 0)
		{
			env->content = mini->path;
		}
	}
	return (env);
}

void	ft_export_add( t_list_ *list, char *str, t_minis *mini)
{
	t_env	*env;
	char	**export;
	char	*temp;

	env = ft_malloc(1 * sizeof(t_env), NULL);
	export = ft_split(str, '=');
	env->name = ft_strdup(export[0]);
	if (export[1] != NULL && ft_getenv(mini, export[0]) == NULL)
		env->content = ft_strjoin("",
				&mini->split[1][strlen(export[0]) + 1]);
	else if (str[ft_strlen(export[0])] == '=')
	{
		printf("wat\n");
		temp = ft_malloc(1 * sizeof(char), NULL);
		temp[0] = '\0';
		env->content = temp;
	}
	else
		env->content = NULL;
	if (export[1] == NULL)
		env = set_pwd(env, export[0], mini);
	free_split(export);
	export_add(&list, env);
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
