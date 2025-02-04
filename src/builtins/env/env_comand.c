/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_comand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:08:21 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/22 14:59:44 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*get_env(void *point, void *locate)
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
			return (get.content);
		}
	}
	return (NULL);
}

void	ft_env(t_minis *mini)
{
	t_token	*token;
	t_list_	*list;
	char	*comand;

	list = mini->tokens;
	if (not_opcion(mini, "env") == TRUE)
		return ;
	while (mini->tokens != NULL)
	{
		token = get_token(mini->tokens);
		comand = expand_env(token->token, mini);
		if (ft_strncmp(token->type, "argument", 15) == 0)
		{
			ft_print_error("env", comand, TOO_ARG, "bash");
			mini->exit_code_error = 1;
			ft_free(comand, NULL);
			return ;
		}
		mini->tokens = mini->tokens->next;
	}
	mini->tokens = list;
	print_list(mini->env, print_env);
}

char	*ft_getenv(t_minis *mini, char *var)
{
	return ((char *)get_list(mini->env, var, get_env));
}

t_env	*new_node_une(char *s1, char *s2)
{
	t_env	*var;
	char	*content;

	var = (t_env *)ft_malloc(1 * sizeof (t_env), NULL);
	content = s2;
	var->name = ft_strdup(s1);
	var->content = ft_strdup(content);
	var->chek = FALSE;
	return (var);
}
