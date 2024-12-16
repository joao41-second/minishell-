/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:41:07 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/16 13:57:38 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_token(void *content)
{
	t_list	*list;
	t_token	*token;

	list = (t_list *)content;
	if(list == NULL)
		return ;
	token = (t_token *)list->content;
	ft_free(token->token, NULL);
	ft_free(token->type, NULL);
	ft_free(token->redirection_target, NULL);
	ft_free(token->redirection_source, NULL);
	ft_free(token, NULL);
}

t_list_ *initialize_tokenizer(t_minis *mini, char ***env_matrix)
{
    t_list_ *token_list;

    token_list = ft_node_new(create_token("", "", "", ""));
    *env_matrix = env_to_matrix(mini);
    return token_list;
}

void finalize_tokens(t_list_ *token_list, char **env_matrix, t_minis *mini)
{
    set_redirection_relations(token_list);
    if (env_matrix)
        free_env_matrix(env_matrix);
}

t_list_ *initialize_and_finalize_tokenizer(t_minis *mini, char ***env_matrix)
{
    t_list_ *token_list;

    token_list = initialize_tokenizer(mini, env_matrix);
    finalize_tokens(token_list, *env_matrix, mini);
    return (token_list);
}
