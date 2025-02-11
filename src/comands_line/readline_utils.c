/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:42:24 by rui               #+#    #+#             */
/*   Updated: 2025/02/11 16:58:47 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chek_expand(char *str, t_minis *mini)
{
	char	*line;

	line = expand_env(ft_strdup(str), mini);
	if (ft_strncmp(line, "", 10) == 0)
	{
		ft_free(line, NULL);
		return (FALSE);
	}
	ft_free(line, NULL);
	return (TRUE);
}

int	chek_comand(t_minis *mini)
{
	t_list_	*list;
	int		bil;
	int		pipe;
	char	*ok;

	list = mini->tokens;
	pipe = 0;
	bil = 0;
	while (list != NULL)
	{
		ok = (expand_env(get_token(list)->token, mini));
		if (ft_strncmp(get_token(list)->type, "pipe", 10) == 0)
			pipe++;
		if (chek_biltin_cmd(ok) == TRUE
			&& ft_strncmp(get_token(list)->type, "command", 30) == 0)
			bil = 1;
		list = list->next;
		ft_free(ok, NULL);
	}
	if (pipe != 0)
		return (FALSE);
	if (bil != 0 && pipe == 0)
		return (TRUE);
	return (FALSE);
}

void	set_error_env(t_minis *mini)
{
	t_env	*code_error_env;

	mini->env = ft_node_start(mini->env);
	code_error_env = list_to_env(
			(t_list_ *)get_list(mini->env, "?", get_env_node));
	ft_free(code_error_env->content, NULL);
	code_error_env->content = ft_itoa(mini->exit_code_error);
	code_error_env = list_to_env(
			(t_list_ *)get_list(mini->env_org, "?", get_env_node));
	ft_free(code_error_env->content, NULL);
	code_error_env->content = ft_itoa(mini->exit_code_error);
}
