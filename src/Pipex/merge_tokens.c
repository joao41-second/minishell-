/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:17:19 by rpires-c          #+#    #+#             */
/*   Updated: 2025/01/08 16:12:12 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_btree *create_tree_node(char *cmd)
{
    t_btree *new_node;

    new_node = (t_btree *)ft_malloc(sizeof(t_btree), NULL);
    if (!new_node)
        return (NULL);
    new_node->cmd = ft_strdup(cmd);
    new_node->left = NULL;
    new_node->right = NULL;
    return (new_node);
}

void deep_copy_tokens(t_list_ *original_tokens, t_list_ **merged_list)
{
	t_list_	*current_original;
	t_token	*original_token;
	char	*new_token;
	char	*new_type;
	char	*new_target;
	char	*new_source;

	current_original = original_tokens;
	while (current_original != NULL)
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
	t_list_	*current;
	t_token	*command_token = NULL;
	t_list_	*temp;
	t_token	*current_token;
	char	*new_token;
	char	*updated_token;

	current = *merged_list;
	while (current)
	{
		current_token = (t_token *)current->content;
		if (ft_strcmp(current_token->type, "command") == 0)
		{
			if (ft_strcmp(current_token->token, "cd") == 0
				|| ft_strcmp(current_token->token, "echo") == 0
				|| ft_strcmp(current_token->token, "env") == 0
				|| ft_strcmp(current_token->token, "exit") == 0
				|| ft_strcmp(current_token->token, "export") == 0
				|| ft_strcmp(current_token->token, "pwd") == 0
				|| ft_strcmp(current_token->token, "unset") == 0)
				current_token->type = "builtin";
			command_token = current_token;
		}
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
			continue ;
		}
		else if (ft_strcmp(current_token->type, "pipe") == 0)
			command_token = NULL;
		current = current->next;
	}
}

t_btree *build_command_tree(t_list_ *merged_list)
{
    t_btree *root;
    t_btree *current_pipe;
    t_token *current_token;

    if (!merged_list)
        return (NULL);
    current_token = (t_token *)merged_list->content;
    root = create_tree_node("|");
    current_pipe = root;
    current_pipe->left = create_tree_node(current_token->token);
    merged_list = merged_list->next;
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

t_btree *token_merger(t_minis *mini)
{
    t_list_ *merged_list;
    t_list_ *save;
	t_btree *command_tree;

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
