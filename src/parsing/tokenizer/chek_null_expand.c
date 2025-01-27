/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_null_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:19:23 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/27 09:19:53 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*convert_list_in_char(t_list_ **list)
{
	char	*line;
	char	*temp;

	line = ft_strdup("");
	while ((*list) != NULL)
	{
		temp = ft_strjoin(line, " ");
		ft_free(line, NULL);
		line = ft_strdup(temp);
		ft_free(temp, NULL);
		temp = ft_strjoin(line, get_token(*list)->token);
		ft_free(line, NULL);
		line = ft_strdup(temp);
		ft_free(temp, NULL);
		if ((*list)->next == NULL)
			break ;
		(*list) = (*list)->next;
	}
	return (line);
}

void	set_token_lists(t_minis *mini)
{
	free_list(mini->tokens_copy, free_token);
	free_list(mini->tokens, free_token);
	mini->tokens = tokenize_and_check_bash_command(mini);
	mini->tokens_copy = tokenize_and_check_bash_command(mini);
}

void	convert_chekline(t_minis *mini)
{
	t_list_	*list_start;
	char	*expand;
	char	*line;

	list_start = mini->tokens;
	expand = expand_env(get_token(mini->tokens)->token, mini);
	while (mini->tokens != NULL )
	{
		ft_free(expand, NULL);
		expand = expand_env(get_token(mini->tokens)->token, mini);
		if (ft_strncmp(expand, "", 50) == 0)
			ft_free_node(&mini->tokens, free_token);
		if (mini->tokens->next == NULL)
			break ;
		mini->tokens = mini->tokens->next;
	}
	ft_free(expand, NULL);
	mini->tokens = ft_node_start(mini->tokens);
	line = convert_list_in_char(&mini->tokens);
	ft_free(mini->line, NULL);
	mini->line = line;
	set_token_lists(mini);
	ft_free(expand, NULL);
}
