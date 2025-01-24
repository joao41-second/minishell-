/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:43:45 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/24 14:53:18 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
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

void	echo_logic(t_minis *mini, t_token *token, int *new_line, int i)
{
	char	*str;

	token = get_token(mini->tokens->next);
	if (token->token[0] == '-')
	{
		while (token->token[++i] != '\0' )
		{
			if (token->token[i] != 'n')
				*new_line = FALSE;
		}
	}
	else
		*new_line = FALSE;
	if (mini->tokens->next != NULL && new_line == TRUE)
		mini->tokens = mini->tokens->next;
	else if (*new_line == FALSE)
		mini->tokens = mini->tokens->next;
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
	if (mini->tokens != NULL && mini->tokens->next != NULL)
	{
		echo_logic(mini, token, &new_line, i);
	}
	if (new_line == FALSE)
		printf("\n");
}
