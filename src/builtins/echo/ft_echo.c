/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:43:45 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/30 16:36:59 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <asm-generic/errno.h>
#include <stdio.h>

void	rm_char_str(char *str, int len)
{
	char	*src;
	int		i;

	len++;
	i = ft_strlen(str);
	src = ft_malloc(ft_strlen(str), NULL);
	ft_strlcpy(src, str, len);
	ft_strlcat(src, &str[len], i);
	ft_bzero(str, i);
	ft_strlcat(str, src, i);
}

void	next_opcion(t_list_ **list)
{
	int	i;

	i = 0;
	while (*list != NULL)
	{
		if (get_token(*list)->token[0] == '-' )
		{
			while (get_token(*list)->token[++i] != '\0')
				if (get_token(*list)->token[i] != 'n')
					i = -50;
			if (i == -50)
				*list = (*list)->previous;
			else
				*list = (*list)->next;
			return ;
		}
		else
			return ;
		if ((*list)->next == NULL)
			break ;
		*list = (*list)->next;
	}
}

void	echo_logic(t_minis *mini, t_token *token, int *new_line, int i)
{
	char	*str;

	token = get_token(mini->tokens->next);
	if (token->token[0] == '-')
	{
		while (token->token[++i] != '\0' )
			if (token->token[i] != 'n')
				*new_line = FALSE;
	}
	else
		*new_line = FALSE;
	if (mini->tokens->next != NULL )
		mini->tokens = mini->tokens->next;
	next_opcion(&mini->tokens);
	while (mini->tokens != NULL)
	{
		str = expand_env(get_token(mini->tokens)->token, mini);
		printf("%s", str);
		if (mini->tokens->next != NULL)
			printf(" ");
		mini->tokens = mini->tokens->next;
	}
}

void	ft_echo(t_minis *mini)
{
	int		i;
	int		new_line;
	t_token	*token;

	i = 0;
	new_line = TRUE;
	token = NULL;
	mini->tokens = ft_node_start(mini->tokens);
	if(mini->tokens->next == NULL)
		printf("\n");
	if (mini->tokens != NULL && mini->tokens->next != NULL)
	{
		echo_logic(mini, token, &new_line, i);
	}
	if (new_line == FALSE)
		printf("\n");
}
