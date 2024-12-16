/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:17:19 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/16 15:01:57 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void deep_copy_tokens(t_list_ *original_tokens, t_list_ **merged_list)
{
	t_list_	*current_original;
	t_token	*original_token;
	char	*new_token;
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

void join_arguments_to_commands(t_list_ **merged_list)
{
    t_list_ *current;
    t_token *command_token;
    t_list_ *temp;
    t_token *current_token;
    char *new_token;
    char *updated_token;

	current = *merged_list;
	command_token = NULL;
	while (current)
	{
		current_token = (t_token *)current->content;
		if (ft_strcmp(current_token->type, "command") == 0)
			command_token = current_token;
		else if (command_token && ft_strcmp(current_token->type, "argument") == 0)
		{
			new_token = ft_strjoin(command_token->token, " ");
			updated_token = ft_strjoin(new_token, current_token->token);
			ft_free(command_token->token, NULL);
			command_token->token = updated_token;
			ft_free(new_token, NULL);
			temp = current->next;
			ft_free_node(&current, free_token);
			current = temp;
		}
		else
			command_token = NULL;
		current = current->next;
	}
}

t_list_ *token_merger(t_minis *mini)
{
	t_list_	*merged_list;

	deep_copy_tokens(mini->tokens, &merged_list);
	join_arguments_to_commands(&merged_list);
	return (merged_list);
}
char	*new_type;
	