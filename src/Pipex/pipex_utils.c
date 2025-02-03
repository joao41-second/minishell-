/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:26:26 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/03 23:15:03 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		open_file_error();
	return (file);
}

t_btree	*create_tree_node(char *cmd)
{
	t_btree	*new_node;

	new_node = (t_btree *)ft_malloc(sizeof(t_btree), NULL);
	if (!new_node)
		return (NULL);
	new_node->cmd = ft_strdup(cmd);
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->redir = NULL;
	return (new_node);
}

void	deep_copy_tokens(t_list_ *original_tokens, t_list_ **merged_list)
{
	t_list_	*current_original;
	t_token	*original_token;

	current_original = original_tokens;
	while (current_original != NULL)
	{
		original_token = (t_token *)current_original->content;
		add_to_list(merged_list, create_token(
				ft_strdup(original_token->token),
				ft_strdup(original_token->type),
				ft_strdup(original_token->redirection_target),
				ft_strdup(original_token->redirection_source)));
		if (current_original->next != NULL && original_token->type
			&& ft_strcmp(original_token->type, "redir") == 0)
			current_original = current_original->next;
		current_original = current_original->next;
	}
}

t_btree	*process_pipe_commands(t_list_ *merged_list, t_btree *root)
{
	t_btree	*current_pipe;
	t_token	*current_token;

	current_pipe = root;
	while (merged_list)
	{
		current_token = (t_token *)merged_list->content;
		if (ft_strcmp(current_token->type, "pipe") == 0)
		{
			current_pipe->right = create_tree_node("|");
			current_pipe = current_pipe->right;
			if (merged_list->next)
			{
				merged_list = merged_list->next;
				current_token = (t_token *)merged_list->content;
				current_pipe->left = create_tree_node(current_token->token);
			}
		}
		merged_list = merged_list->next;
	}
	current_pipe->right = NULL;
	return (root);
}
