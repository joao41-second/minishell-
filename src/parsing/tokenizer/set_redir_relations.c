/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_relations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:32:52 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/25 17:42:18 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void set_output_redirection(t_list_ *current, t_token *token)
{
    t_token *found_source = NULL;
    t_token *found_target = NULL;

	found_target = NULL;
	found_source = NULL;
    if (current->previous && 
        ((t_token *)current->previous->content)->token)
    {
        found_source = (t_token *)current->previous->content;
        token->redirection_source = ft_strdup(found_source->token);
    }
    if (current->next && 
        ((t_token *)current->next->content)->token)
    {
        found_target = (t_token *)current->next->content;
        token->redirection_target = ft_strdup(found_target->token);
    }
}

static void find_target_backwards(t_list_ *current, t_token *token)
{
    t_list_ *search;
	t_token *potential_target;

	search = current->previous;
    while (search)
    {
        potential_target = (t_token *)search->content;
        if (potential_target && potential_target->type &&
            ft_strcmp(potential_target->type, "redir") != 0 &&
            ft_strcmp(potential_target->type, "append") != 0)
        {
            token->redirection_target = ft_strdup(potential_target->token);
            break ;
        }
        search = search->previous;
    }
}

static void find_source_forwards(t_list_ *current, t_token *token)
{
    t_list_ *search;
	t_token *potential_source;

	search = current->next;
    while (search)
    {
        potential_source = (t_token *)search->content;
        if (potential_source && potential_source->type &&
            ft_strcmp(potential_source->type, "redir") != 0 &&
            ft_strcmp(potential_source->type, "append") != 0)
        {
            token->redirection_source = ft_strdup(potential_source->token);
            break ;
        }
        search = search->next;
    }
}

static void find_input_redirection(t_list_ *current, t_token *token)
{
    find_target_backwards(current, token);
    find_source_forwards(current, token);
}

static int is_redirection_token(t_token *token)
{
    return (token && 
            (ft_strcmp(token->type, "redir") == 0 || 
            ft_strcmp(token->type, "append") == 0));
}

void set_redirection_relations(t_list_ *list)
{
    t_list_ *current = list;

    while (current)
    {
        t_token *token = (t_token *)current->content;

        if (is_redirection_token(token))
        {
            if (!ft_strcmp(token->token, ">") || !ft_strcmp(token->token, ">>"))
                set_output_redirection(current, token);
            else
                find_input_redirection(current, token);
        }

        current = current->next;
    }
}

/* static void set_redirection_relations(t_list_ *list)
{
    t_list_ *current;
    t_token *token;
    t_list_ *search;
    t_token *found_target;
    t_token *found_source;

    current = list;
    while (current)
    {
        token = (t_token *)current->content;
        if (token && (ft_strcmp(token->type, "redir") == 0 || 
                     ft_strcmp(token->type, "append") == 0))
        {
            found_target = NULL;
            found_source = NULL;
            if (!ft_strcmp(token->token, ">") || !ft_strcmp(token->token, ">>"))
            {
                if (current->previous && 
                    ((t_token *)current->previous->content)->token)
                {
                    found_source = (t_token *)current->previous->content;
                    token->redirection_source = ft_strdup(found_source->token);
                }
                if (current->next && 
                    ((t_token *)current->next->content)->token)
                {
                    found_target = (t_token *)current->next->content;
                    token->redirection_target = ft_strdup(found_target->token);
                }
            }
            else 
            {
                search = current->previous;
                while (search)
                {
                    t_token *potential_target = (t_token *)search->content;
                    if (potential_target && potential_target->type && 
                        ft_strcmp(potential_target->type, "redir") != 0 &&
                        ft_strcmp(potential_target->type, "append") != 0)
                    {
                        found_target = potential_target;
                        token->redirection_target = ft_strdup(found_target->token);
                        break;
                    }
                    search = search->previous;
                }
                search = current->next;
                while (search)
                {
                    t_token *potential_source = (t_token *)search->content;
                    if (potential_source && potential_source->type && 
                        ft_strcmp(potential_source->type, "redir") != 0 &&
                        ft_strcmp(potential_source->type, "append") != 0)
                    {
                        found_source = potential_source;
                        token->redirection_source = ft_strdup(found_source->token);
                        break;
                    }
                    search = search->next;
                }
            }
        }
        current = current->next;
    }
} */