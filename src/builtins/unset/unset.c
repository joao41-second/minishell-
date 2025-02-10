/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:06:26 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/03 10:20:41 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*get_env_node(void *point, void *locate)
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
			return (point);
		}
	}
	return (NULL);
}

int	chek_varabel(t_env *env, t_list_ **list, char *str)
{
	if (*list == NULL)
		return (TRUE);
	if (ft_strncmp(str, "PWD", 23) == 0)
	{
		env = ft_getenv_content(*list, "PWD");
		env->chek = FALSE;
		ft_free(env->content, NULL);
		env->content = NULL;
		return (TRUE);
	}
	if (ft_strncmp(str, "OLDPWD", 23) == 0)
	{
		env = ft_getenv_content(*list, "OLDPWD");
		env->chek = FALSE;
		ft_free(env->content, NULL);
		env->content = NULL;
		return (TRUE);
	}
	return (FALSE);
}

void	unset_list(t_list_ **list, char *str)
{
	t_list_	*ok;
	t_env	*env;

	env = NULL;
	if (chek_varabel(env, list, str) == TRUE)
		return ;
	ok = *list;
	ok = ft_node_start(ok);
	ok = (t_list_ *)get_list(*list, str, get_env_node);
	if (ok == NULL)
		return ;
	ft_free_node(&ok, free_env);
	ok = ft_node_start(ok);
	*list = ok;
}

void	ft_unset(t_minis *mini)
{
	t_token	*token;

	if (not_opcion(mini, "unset") == TRUE)
		return ;
	if (mini->tokens != NULL && mini->tokens->next != NULL)
	{
		mini->tokens = mini->tokens->next;
		while (mini->tokens != NULL)
		{
			token = get_token(mini->tokens);
			unset_list(&mini->env, token->token);
			unset_list(&mini->env_org, token->token);
			if (mini->tokens->next == NULL)
				break ;
			mini->tokens = mini->tokens->next;
		}
	}
}
