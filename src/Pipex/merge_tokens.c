/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:17:19 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/03 23:14:24 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_builtin_type(t_token *current_token)
{
	if (ft_strcmp(current_token->token, "cd") == 0
		|| ft_strcmp(current_token->token, "echo") == 0
		|| ft_strcmp(current_token->token, "env") == 0
		|| ft_strcmp(current_token->token, "exit") == 0
		|| ft_strcmp(current_token->token, "export") == 0
		|| ft_strcmp(current_token->token, "pwd") == 0
		|| ft_strcmp(current_token->token, "unset") == 0)
		current_token->type = "builtin";
}

t_list_	*merge_argument_with_command(t_list_ *current, t_token *command_token)
{
	t_list_	*temp;
	char	*new_token;
	char	*updated_token;
	t_token	*current_token;

	current_token = (t_token *)current->content;
	new_token = ft_strjoin(command_token->token, " ");
	updated_token = ft_strjoin(new_token, current_token->token);
	ft_free(command_token->token, NULL);
	command_token->token = updated_token;
	ft_free(new_token, NULL);
	temp = current->next;
	ft_free_node(&current, free_token);
	return (temp);
}

void	join_arguments_to_commands(t_list_ **merged_list)
{
	t_list_	*current;
	t_token	*command_token;
	t_token	*current_token;

	current = *merged_list;
	command_token = NULL;
	while (current)
	{
		current_token = (t_token *)current->content;
		if (ft_strcmp(current_token->type, "command") == 0)
		{
			set_builtin_type(current_token);
			command_token = current_token;
		}
		else if (command_token
			&& ft_strcmp(current_token->type, "argument") == 0)
		{
			current = merge_argument_with_command(current, command_token);
			continue ;
		}
		else if (ft_strcmp(current_token->type, "pipe") == 0)
			command_token = NULL;
		current = current->next;
	}
}

t_btree	*build_command_tree(t_list_ *merged_list)
{
	t_btree	*root;
	t_token	*current_token;

	if (!merged_list)
		return (NULL);
	current_token = (t_token *)merged_list->content;
	root = create_tree_node("|");
	root->left = create_tree_node(current_token->token);
	merged_list = merged_list->next;
	return (process_pipe_commands(merged_list, root));
}

t_btree	*token_merger(t_minis *mini)
{
	t_list_	*merged_list;
	t_list_	*save;
	t_btree	*command_tree;

	merged_list = ft_node_new(create_token("", "", "", ""));
	deep_copy_tokens(mini->tokens, &merged_list);
	save = merged_list;
	merged_list = merged_list->next;
	ft_free_node(&save, free_token);
	merged_list = ft_node_start(merged_list);
	join_arguments_to_commands(&merged_list);
	command_tree = build_command_tree(merged_list);
	return (command_tree);
}
