/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:05:55 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/03 10:00:34 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdbool.h>

t_env	*set_env_in_export(t_list_ *list, char *str, char **export)
{
	t_env	*env;
	char	*temp;
	int		i;

	i = 0;
	if (str[ft_strlen(export[0]) - 1] == '+')
	{
		temp = ft_substr(export[0], 0, ft_strlen(export[0]) - 1);
		ft_free(export[0], NULL);
		export[0] = temp;
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
		env = new_tenv();
	return (env);
}

int	set_env_in_case_of_the_plus(char *str, char **export,
								t_env *env, char *temp)
{
	int	i;

	i = 0;
	if (str[ft_strlen(export[0]) - 1] == '+')
	{
		temp = ft_substr(export[0], 0, ft_strlen(export[0]) - 1);
		env->name = temp;
		temp = NULL;
		i++;
	}
	else
		env->name = ft_strdup(export[0]);
	return (i);
}

int	inicilaze_variabel(t_env **env, char ***export, t_list_ *list, char *str)
{
	char	*temp;

	temp = NULL;
	*export = ft_split(str, '=');
	*env = set_env_in_export(list, str, *export);
	free_split(*export);
	*export = ft_split(str, '=');
	return (set_env_in_case_of_the_plus(str, *export, *env, temp));
}

void	ft_export_add( t_list_ *list, char *str, t_minis *mini)
{
	t_env	*env;
	char	**export;
	char	*temp;
	int		i;

	i = inicilaze_variabel(&env, &export, list, str);
	if (export[1] != NULL && i == 0)
		env->content = ft_strjoin("",
				&str[strlen(export[0]) + 1]);
	else if (str[ft_strlen(export[0])] == '=' && i == 0)
	{
		temp = ft_malloc(1 * sizeof(char), NULL);
		temp[0] = '\0';
		env->content = temp;
	}
	else if (export[1] != NULL && i == 1)
	{
		temp = ft_strjoin(env->content, ft_strjoin("",
					&str[strlen(export[0]) + 1]));
		ft_free(env->content, NULL);
		env->content = temp;
	}
	if (ft_getenv_content(list, env->name) == NULL)
		export_add(&list, env);
	free_split(export);
}

int	valid_export(char	*token)
{
	int	i;

	i = 0;
	if (ft_isalpha(token[0]) == TRUE)
		return (FALSE);
	while (token[++i] != '\0')
	{
		if (token[i] == '=')
		{
			if (token[i - 1] != '+' && ft_isalnum(token[i - 1]) == TRUE)
				return (FALSE);
		}
	}
	if (token[--i] != '+' && token[--i] != '='
		&& ft_isalnum(token[--i]) == TRUE)
		return (FALSE);
	return (TRUE);
}

int	locate(char *str, char src)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == src)
			return (TRUE);
	}
	return (FALSE);
}

void	ft_export(t_minis *mini)
{
	t_token	*token;
	t_list_	*list;

	list = mini->tokens;
	if (mini->tokens != NULL && mini->tokens->next != NULL)
	{
		token = get_token(list->next);
		if (locate(token->token, '=') == FALSE
			&& not_opcion(mini, "export") == TRUE)
			return ;
		list = list->next;
		while (list != NULL)
		{
			token = get_token(list);
			if (valid_export(token->token) == TRUE)
			{
				ft_export_add(mini->env, token->token, mini);
				ft_export_add(mini->env_org, token->token, mini);
			}
			else
				return (ft_print_error("export", token->token,
						SNTAX_ERROR, "bash"));
			list = list->next;
		}
	}
	if (mini->tokens->next == NULL)
		organizer_list(mini->env_org);
}
