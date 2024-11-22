/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:01:39 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/22 17:36:59 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

// Helper function to check if character is a quote
static int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

// Helper function to create a new token node
static t_token *create_token(char *str, char *type)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->token = ft_strdup(str);
    token->type = ft_strdup(type);
    token->redirection_target = NULL;
    token->redirection_source = NULL;
    return (token);
}

// Helper function to add node to list
static void add_to_list(t_list_ **list, t_token *token)
{
    t_list_ *new;
    t_list_ *last;

    new = (t_list_ *)malloc(sizeof(t_list_));
    if (!new)
        return;
    new->content = token;
    new->next = NULL;
    if (!*list)
    {
        new->previous = NULL;
        *list = new;
        return;
    }
    last = *list;
    while (last->next)
        last = last->next;
    last->next = new;
    new->previous = last;
}

// Helper function to extract quoted string
static int extract_quoted_string(char *line, int *i, char **token)
{
    char quote;
    int start;
    int len;

    quote = line[*i];
    start = *i;
    (*i)++;
    while (line[*i] && line[*i] != quote)
        (*i)++;
    if (line[*i] == quote)
        (*i)++;
    len = *i - start;
    *token = (char *)malloc(len + 1);
    if (!*token)
        return (0);
    ft_strlcpy(*token, line + start, len + 1);
    return (1);
}

// Helper function to check if string is a redirection
static char *get_redirection_type(char *str)
{
    if (!ft_strcmp(str, ">"))
        return (ft_strdup("redir"));
    if (!ft_strcmp(str, "<"))
        return (ft_strdup("redir"));
    if (!ft_strcmp(str, ">>"))
        return (ft_strdup("append"));
    if (!ft_strcmp(str, "<<"))
        return (ft_strdup("append"));
    return (NULL);
}

static void set_redirection_relations(t_list_ *list)
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

            // For ">" and ">>" - source is before, target is after
            if (!ft_strcmp(token->token, ">") || !ft_strcmp(token->token, ">>"))
            {
                // Find source (previous token)
                if (current->previous && 
                    ((t_token *)current->previous->content)->token)
                {
                    found_source = (t_token *)current->previous->content;
                    token->redirection_source = ft_strdup(found_source->token);
                }

                // Find target (next token)
                if (current->next && 
                    ((t_token *)current->next->content)->token)
                {
                    found_target = (t_token *)current->next->content;
                    token->redirection_target = ft_strdup(found_target->token);
                }
            }
            // For "<" and "<<" - target is before, source is after
            else 
            {
                // Search backward for target (first non-redirection token)
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

                // Search forward for source (first non-redirection token)
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
}

static void modify_token_types(t_list_ *token_list)
{
    int first_command_seen = 0;
    t_list_ *current = token_list;

    while (current)
    {
        t_token *token = (t_token *)current->content;
        
        // Reset logic for pipe token
        if (token && ft_strcmp(token->type, "pipe") == 0)
            first_command_seen = 0;
        
        // Modify command tokens
        if (token && ft_strcmp(token->type, "command") == 0)
        {
            if (first_command_seen)
            {
                free(token->type);
                token->type = ft_strdup("argument");
            }
            else
                first_command_seen = 1;
        }
        
        current = current->next;
    }
}

// Main tokenization function
t_list_ *tokenizeAndCheckBashCommand(t_minis *mini)
{
    t_list_ *token_list;
    char *line;
    int i;
    char *current_token;
    int token_start;
    char **env_matrix;

    token_list = NULL;
    line = mini->line;
    i = 0;
    env_matrix = env_to_matrix(mini);

    while (line[i])
    {
        // Skip whitespace
        while (line[i] && is_whitespace(line[i]))
            i++;
        if (!line[i])
            break;

        // Handle quotes
        if (is_quote(line[i]))
        {
            if (!extract_quoted_string(line, &i, &current_token))
                continue;
            add_to_list(&token_list, create_token(current_token, "argument"));
            free(current_token);
            continue;
        }

        // Handle redirections and pipes
        if (line[i] == '>' || line[i] == '<' || line[i] == '|')
        {
            token_start = i;
            if ((line[i] == '>' && line[i + 1] == '>') || 
                (line[i] == '<' && line[i + 1] == '<'))
            {
                current_token = ft_substr(line, i, 2);
                i += 2;
            }
            else
            {
                current_token = ft_substr(line, i, 1);
                i++;
            }
            if (current_token[0] == '|')
                add_to_list(&token_list, create_token(current_token, "pipe"));
            else
                add_to_list(&token_list, create_token(current_token, 
                           get_redirection_type(current_token)));
            free(current_token);
            continue;
        }

        // Handle regular tokens
        token_start = i;
        while (line[i] && !is_whitespace(line[i]) && 
               !is_quote(line[i]) && line[i] != '>' && 
               line[i] != '<' && line[i] != '|')
            i++;
        current_token = ft_substr(line, token_start, i - token_start);

        // Check if token is a command, env_var, or argument
        if (current_token[0] == '$')
            add_to_list(&token_list, create_token(current_token, "env_var"));
        else
        {
            char *path = find_path(current_token, env_matrix);
            if (path)
            {
                add_to_list(&token_list, create_token(current_token, "command"));
                free(path);
            }
            else
                add_to_list(&token_list, create_token(current_token, "argument"));
        }
        free(current_token);
    }

    // Handle redirection relationships
    set_redirection_relations(token_list);

    // Clean up
    if (env_matrix)
    {
        i = 0;
        while (env_matrix[i])
            free(env_matrix[i++]);
        free(env_matrix);
    }

    modify_token_types(token_list);
    return (token_list);
}