/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:01:39 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/25 18:14:35 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

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

static void modify_token_types(t_list_ *token_list, t_minis *mini)
{
    int first_command_seen = 0;
    t_list_ *current = token_list;

    while (current)
    {
        t_token *token = (t_token *)current->content;

        if (token && ft_strcmp(token->type, "pipe") == 0)
            first_command_seen = 0;
        if (token && (ft_strcmp(token->type, "command") == 0 || 
                     (ft_strncmp(token->token, "\"", 1) == 0 || 
                      ft_strncmp(token->token, "'", 1) == 0)))
        {
            char *stripped_token = token->token;
            if ((stripped_token[0] == '"' || stripped_token[0] == '\'') && 
                stripped_token[0] == stripped_token[ft_strlen(stripped_token) - 1])
                stripped_token = ft_substr(stripped_token, 1, ft_strlen(stripped_token) - 2);
            char **env_matrix = env_to_matrix(mini);
            char *path = find_path(stripped_token, env_matrix);
            
            if (path)
            {
                if (first_command_seen)
                {
                    free(token->type);
                    token->type = ft_strdup("argument");
                }
                else
                    first_command_seen = 1;
                
                free(path);
            }
            else
            {
                free(token->type);
                token->type = ft_strdup("argument");
            }
            if (env_matrix)
            {
                int i = 0;
                while (env_matrix[i])
                    free(env_matrix[i++]);
                free(env_matrix);
            }
            if (stripped_token != token->token)
                free(stripped_token);
        }
        
        current = current->next;
    }
}

static int is_quoted_string_command(char *str, char **env_matrix)
{
    if ((str[0] == '"' || str[0] == '\'') && 
        str[0] == str[strlen(str) - 1])
    {
        char *stripped = ft_substr(str, 1, strlen(str) - 2);
        char *path = find_path(stripped, env_matrix);
        free(stripped);
        if (path)
        {
            free(path);
            return 1;
        }
    }
    return 0;
}

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
        while (line[i] && is_whitespace(line[i]))
            i++;
        if (!line[i])
            break;
        if (is_quote(line[i]))
        {
            if (!extract_quoted_string(line, &i, &current_token))
                continue;
            char **env_matrix = env_to_matrix(mini);
            int is_command = is_quoted_string_command(current_token, env_matrix);
            if (env_matrix)
            {
                int j = 0;
                while (env_matrix[j])
                    free(env_matrix[j++]);
                free(env_matrix);
            }
            add_to_list(&token_list, 
                create_token(current_token, 
                    is_command ? "command" : "argument"));
            
            free(current_token);
            continue;
        }
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
        token_start = i;
        while (line[i] && !is_whitespace(line[i]) && 
               !is_quote(line[i]) && line[i] != '>' && 
               line[i] != '<' && line[i] != '|')
            i++;
        current_token = ft_substr(line, token_start, i - token_start);
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
    set_redirection_relations(token_list);
    if (env_matrix)
    {
        i = 0;
        while (env_matrix[i])
            free(env_matrix[i++]);
        free(env_matrix);
    }
    modify_token_types(token_list, mini);
    return (token_list);
}