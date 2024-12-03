/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:56:03 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/03 11:39:44 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

t_token	*create_token(char *str, char *type)
{
	t_token	*token;

	token = (t_token *)ft_malloc(sizeof(t_token) * 1, NULL);
	if (!token)
		return (NULL);
	token->token = ft_strdup(str);
	ft_free(str, NULL);
	token->type = ft_strdup(type);
	ft_free(type, NULL);
	token->redirection_target = NULL;
	token->redirection_source = NULL;
	return (token);
}

void add_to_list(t_list_ **list, t_token *token)
{
    t_list_ *new_node;

    new_node = ft_node_new(token);
    if (!*list)
        *list = new_node;
    else
	{
        t_list_ *last = ft_node_end(*list);
        ft_node_add_front(&last, new_node);
    }
}

char	*get_redirection_type(char *str)
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
