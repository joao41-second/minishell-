/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:17:19 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/13 16:46:33 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void copy_tokens(t_list_ *original_tokens, t_list_ **merged_list)
{
	t_list_	*current_original;
	t_token	*original_token;
	char	*new_token;
	char	*new_type;
	char	*new_target;
	char	*new_source;

	current_original = original_tokens;
	while (current_original)
	{
		original_token = (t_token *)current_original->content;
		new_token = ft_strdup(original_token->token);
		new_type = ft_strdup(original_token->type);
		new_target = ft_strdup(original_token->redirection_target);
		new_source = ft_strdup(original_token->redirection_source);
		add_to_list(merged_list, create_token(new_token, new_type, new_target, new_source));
		if (original_token->type && ft_strcmp(original_token->type, "redir") == 0)
			current_original = current_original->next;
		current_original = current_original->next;
	}
}

t_list_ *token_merger(t_minis *mini)
{
	t_list_	*merged_list;

	copy_tokens(mini->tokens, &merged_list);
	return (merged_list);
}
