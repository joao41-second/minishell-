/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:01:39 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/26 18:08:36 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
