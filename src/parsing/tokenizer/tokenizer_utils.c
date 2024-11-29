/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:56:03 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/29 17:16:03 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_whitespace(char c)
{
	return ((c >= 9 & c <= 13) || c == 32);
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
	token->type = ft_strdup(type);
	token->redirection_target = NULL;
	token->redirection_source = NULL;
	return (token);
}

void	add_to_list(t_list_ **list, t_token *token)
{
	t_list_	*new;
	t_list_	*last;
	new = ft_node_new(token);
	ft_node_end(list);
	ft_node_add_front(list, new);
}

// void	add_to_list(t_list_ **list, t_token *token)
// {
// 	t_list_	*new;
// 	t_list_	*last;

// 	new = (t_list_ *)ft_malloc(sizeof(t_list_), NULL);
// 	if (!new)
// 		return ;
// 	new->content = token;
// 	new->next = NULL;
// 	if (!*list)
// 	{
// 		new->previous = NULL;
// 		*list = new;
// 		return ;
// 	}
// 	last = *list;
// 	while (last->next)
// 		last = last->next;
// 	last->next = new;
// 	new->previous = last;
// }


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
