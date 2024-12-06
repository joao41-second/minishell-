/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:17:19 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/06 18:40:36 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_ *merge_command_tokens(t_list_ *original_list)
{
    t_list_ *current = original_list;
    t_list_ *prev = NULL;
    t_list_ *next = NULL;

    // First pass: remove nodes matching redirection targets
    while (current)
    {
        t_token *current_token = (t_token *)current->content;
        next = current->next;

        // Check if current node is a redir type and has a redirection_target
        if (strcmp(current_token->type, "redir") == 0 && current_token->redirection_target)
        {
            // Search for and remove node with matching redirection_target
            t_list_ *search = original_list;
            t_list_ *search_prev = NULL;

            while (search)
            {
                t_token *search_token = (t_token *)search->content;

                if (strcmp(search_token->token, current_token->redirection_target) == 0)
                {
                    // Unlink the node
                    if (search_prev)
                        search_prev->next = search->next;
                    else
                        original_list = search->next;

                    if (search->next)
                        search->next->previous = search_prev;

                    // Free the node's content
                    free(search_token->token);
                    free(search_token->type);
                    free(search_token->redirection_target);
                    free(search_token->redirection_source);
                    free(search_token);

                    // Free the node itself
                    free(search);
                    break;
                }

                search_prev = search;
                search = search->next;
            }
        }

        current = next;
    }

    // Subsequent processing to merge tokens
    t_list_ *new_list = NULL;
    current = original_list;
    t_list_ *prev_command = NULL;
    t_list_ *new_node = NULL;
    t_list_ *last = NULL;
    t_token *current_token = NULL;
    t_token *new_token = NULL;
    t_token *prev_command_token = NULL;
    char *new_command = NULL;
    size_t new_len = 0;

    while (current)
    {
        current_token = (t_token *)current->content;

        // If current token is a command
        if (strcmp(current_token->type, "command") == 0)
        {
            new_node = malloc(sizeof(t_list_));
            new_token = malloc(sizeof(t_token));
            
            new_token->token = strdup(current_token->token);
            new_token->type = strdup(current_token->type);
            new_token->redirection_target = current_token->redirection_target ? 
                strdup(current_token->redirection_target) : NULL;
            new_token->redirection_source = current_token->redirection_source ? 
                strdup(current_token->redirection_source) : NULL;

            new_node->content = new_token;
            new_node->next = NULL;
            new_node->previous = NULL;

            if (!new_list)
                new_list = new_node;
            else
            {
                last = new_list;
                while (last->next)
                    last = last->next;
                last->next = new_node;
                new_node->previous = last;
            }

            prev_command = new_node;
        }
        // If current token is an argument and there's a previous command
        else if (strcmp(current_token->type, "argument") == 0 && prev_command)
        {
            prev_command_token = (t_token *)prev_command->content;
            
            new_len = strlen(prev_command_token->token) + 
                      strlen(current_token->token) + 2;
            
            new_command = malloc(new_len);
            strcpy(new_command, prev_command_token->token);
            strcat(new_command, " ");
            strcat(new_command, current_token->token);
            
            free(prev_command_token->token);
            prev_command_token->token = new_command;
        }
        else
        {
            new_node = malloc(sizeof(t_list_));
            new_token = malloc(sizeof(t_token));
            
            new_token->token = strdup(current_token->token);
            new_token->type = strdup(current_token->type);
            new_token->redirection_target = current_token->redirection_target ? 
                strdup(current_token->redirection_target) : NULL;
            new_token->redirection_source = current_token->redirection_source ? 
                strdup(current_token->redirection_source) : NULL;

            new_node->content = new_token;
            new_node->next = NULL;
            new_node->previous = NULL;

            if (!new_list)
                new_list = new_node;
            else
            {
                last = new_list;
                while (last->next)
                    last = last->next;
                last->next = new_node;
                new_node->previous = last;
            }

            prev_command = NULL;
        }

        current = current->next;
    }

    return new_list;
}
