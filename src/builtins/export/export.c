/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:05:55 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/26 18:34:33 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*local_use(t_list_ *list, char *str)
{
	t_env	*env;
	char	*temp;
	char	**export;
	int		i;

	i = 0;
	export = ft_split(str, '=');
	if (str[ft_strlen(export[0]) - 1] == '+')
	{
		temp = ft_substr(export[0], 0, ft_strlen(export[0]) - 1);
		ft_free(export[0], NULL);
		export[0] = temp;
		printf("oi o %s, \n", export[0]);
		temp = NULL;
		i++;
	}
	if (ft_getenv_content(list, export[0]) != NULL)
	{
		env = ft_getenv_content(list, export[0]);
		env->chek = TRUE;
		if (export[1] != NULL && i == 0)
			ft_free(env->content, NULL);
	}
	else
	{
		env = ft_malloc(1 * sizeof(t_env), NULL);
		env->content = NULL;
	}
	free_split(export);
	return (env);
}

void	ft_export_add( t_list_ *list, char *str, t_minis *mini)
{
	t_env	*env;
	char	**export;
	char	*temp;
	int		i;

	i = 0;
	export = ft_split(str, '=');
	env = local_use(list, str);
	if (str[ft_strlen(export[0]) - 1] == '+')
	{
		temp = ft_substr(export[0], 0 , ft_strlen(export[0]) - 1);
		env->name = temp;
		temp = NULL;
		i++;
	}
	else
		env->name = ft_strdup(export[0]);
	if (export[1] != NULL && i == 0)
		env->content = ft_strjoin("",
				&mini->split[1][strlen(export[0]) + 1]);
	else if (str[ft_strlen(export[0])] == '=' && i == 0)
	{
		temp = ft_malloc(1 * sizeof(char), NULL);
		temp[0] = '\0';
		env->content = temp;
	}
	else if (export[1] != NULL && i == 1)
	{
		temp = ft_strjoin(env->content, ft_strjoin("",
					&mini->split[1][strlen(export[0]) + 1]));
		ft_free(env->content, NULL);
		env->content = temp;
	}
	if (ft_getenv_content(list, env->name) == NULL)
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
