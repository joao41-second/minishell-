/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:41:07 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/02 17:47:10 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_token(void *content)
{
    t_token *token;

	token = (t_token *)content;
    if (!token)
		return;
    ft_free(token->token, NULL);
    ft_free(token->type, NULL);
    ft_free(token->redirection_target, NULL);
    ft_free(token->redirection_source, NULL);
    ft_free(token, NULL);
}

t_list_ *initialize_tokenizer(t_minis *mini, char ***env_matrix)
{
    t_list_ *token_list;

    token_list = ft_node_new(create_token("", ""));
    *env_matrix = env_to_matrix(mini);
    return token_list;
}

void finalize_tokens(t_list_ *token_list, char **env_matrix, t_minis *mini)
{
    set_redirection_relations(token_list);
    if (env_matrix)
        free_env_matrix(env_matrix);
    modify_token_types(token_list, mini);
}

t_list_ *initialize_and_finalize_tokenizer(t_minis *mini, char ***env_matrix)
{
    t_list_ *token_list;

    token_list = initialize_tokenizer(mini, env_matrix);
    finalize_tokens(token_list, *env_matrix, mini);
    return (token_list);
}

void	process_quoted_string(char *line, int *i,
						char ***env_matrix, t_list_ **token_list)
{
	char	*current_token;
	int		is_command;

	if (!extract_quoted_string(line, i, &current_token))
		return ;
	is_command = is_quoted_string_command(current_token, *env_matrix);
	if (is_command)
		add_to_list(token_list, create_token(current_token, "command"));
	else
		add_to_list(token_list, create_token(current_token, "argument"));
	ft_free(current_token, NULL);
}
