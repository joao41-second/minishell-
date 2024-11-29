/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_relations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:32:52 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/29 15:31:42 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	set_output_redirection(t_list_ *current, t_token *token)
{
	t_token	*found_source;
	t_token	*found_target;

	found_target = NULL;
	found_source = NULL;
	if (current->previous
		&& ((t_token *)current->previous->content)->token)
	{
		found_source = (t_token *)current->previous->content;
		token->redirection_source = ft_strdup(found_source->token);
	}
	if (current->next
		&& ((t_token *)current->next->content)->token)
	{
		found_target = (t_token *)current->next->content;
		token->redirection_target = ft_strdup(found_target->token);
	}
}

static void	find_target_backwards(t_list_ *current, t_token *token)
{
	t_list_	*search;
	t_token	*potential_target;

	search = current->previous;
	while (search)
	{
		potential_target = (t_token *)search->content;
		if (potential_target && potential_target->type
			&& ft_strcmp(potential_target->type, "redir") != 0
			&& ft_strcmp(potential_target->type, "append") != 0)
		{
			token->redirection_target = ft_strdup(potential_target->token);
			break ;
		}
		search = search->previous;
	}
}

static void	find_source_forwards(t_list_ *current, t_token *token)
{
	t_list_	*search;
	t_token	*potential_source;

	search = current->next;
	while (search)
	{
		potential_source = (t_token *)search->content;
		if (potential_source && potential_source->type
			&& ft_strcmp(potential_source->type, "redir") != 0
			&& ft_strcmp(potential_source->type, "append") != 0)
		{
			token->redirection_source = ft_strdup(potential_source->token);
			break ;
		}
		search = search->next;
	}
}

static int	is_redirection_token(t_token *token)
{
	return (token
		&& (ft_strcmp(token->type, "redir") == 0
			|| ft_strcmp(token->type, "append") == 0));
}

void	set_redirection_relations(t_list_ *list)
{
	t_list_	*current;
	t_token	*token;

	current = list;
	while (current)
	{
		token = (t_token *)current->content;
		if (is_redirection_token(token))
		{
			if (!ft_strcmp(token->token, ">") || !ft_strcmp(token->token, ">>"))
				set_output_redirection(current, token);
			else
			{
				find_target_backwards(current, token);
				find_source_forwards(current, token);
			}
		}
		current = current->next;
	}
}
