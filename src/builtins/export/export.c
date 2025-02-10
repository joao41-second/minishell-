/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:05:55 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/07 16:13:05 by rui              ###   ########.fr       */
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

void	ft_export_add( t_list_ *list, char *str)
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

void	export_add_while(t_minis *mini, t_list_ *list,
					t_token *token, char *comand)
{
	while (list != NULL)
	{
		ft_free(comand, NULL);
		token = get_token(list);
		comand = expand_env(token->token, mini);
		if (valid_export(comand) == TRUE)
		{
			ft_export_add(mini->env, comand);
			ft_export_add(mini->env_org, comand);
		}
		else
		{
			mini->exit_code_error = 1;
			return (ft_print_error("export", comand,
					SYNTAX_ERROR, "bash"), ft_free(comand, NULL));
		}
		list = list->next;
	}
}

void	ft_export(t_minis *mini)
{
	t_token	*token;
	t_list_	*list;
	char	*comand;

	list = mini->tokens;
	if (mini->tokens != NULL && mini->tokens->next != NULL)
	{
		token = get_token(list->next);
		comand = expand_env(token->token, mini);
		if (locate(comand, '=') == FALSE
			&& not_opcion(mini, "export") == TRUE)
			return ;
		list = list->next;
		export_add_while(mini, list, token, comand);
		ft_free(comand, NULL);
	}
	if (mini->tokens->next == NULL)
		organizer_list(mini->env_org);
}
